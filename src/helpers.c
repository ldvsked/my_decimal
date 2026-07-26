#include "my_decimal.h"

void init_decimal(my_decimal *value) { memset(value, 0, sizeof(my_decimal)); }

void set_decimal(my_decimal *dst, unsigned int b0, unsigned int b1,
                 unsigned int b2, int scale, int sign) {
  dst->bits[0] = b0;
  dst->bits[1] = b1;
  dst->bits[2] = b2;
  dst->bits[3] = (scale << 16) | (sign << 31);
}

int get_sign(my_decimal value) { return (value.bits[3] >> 31) & 1; }

void set_sign(my_decimal *value, int sign) {
  if (sign) {
    value->bits[3] |= (1 << 31);
  } else {
    value->bits[3] &= ~(1 << 31);
  }
}

int get_scale(my_decimal value) { return (value.bits[3] >> 16) & 0xFF; }

void set_scale(my_decimal *value, int scale) {
  int sign = get_sign(*value);
  value->bits[3] = (scale << 16);
  set_sign(value, sign);
}

void normalize_scale(my_decimal *value_1, my_decimal *value_2) {
  int scale1 = get_scale(*value_1);
  int scale2 = get_scale(*value_2);
  if (scale1 == scale2) return;
  if (scale1 < scale2) {
    my_decimal temp = *value_1;
    int diff = scale2 - scale1;
    int overflow = 0;
    for (int i = 0; i < diff; i++) {
      if (mul_by_10(&temp) != S21_OK) {
        overflow = 1;
        break;
      }
    }
    if (!overflow) {
      *value_1 = temp;
      set_scale(value_1, scale2);
    } else {
      my_big_decimal big_v2 = decimal_to_big(*value_2);
      int diff_reverse = scale2 - scale1;
      int remainder = 0;
      for (int i = 0; i < diff_reverse; i++) {
        remainder = div_by_10_big(&big_v2);
      }
      bank_rounding(&big_v2, remainder);
      if (!is_overflow_big(big_v2)) {
        big_to_decimal(big_v2, value_2);
        set_scale(value_2, scale1);
      } else {
        set_scale(value_1, scale1);
        set_scale(value_2, scale2);
      }
    }
  } else {
    my_decimal temp = *value_2;
    int diff = scale1 - scale2;
    int overflow = 0;
    for (int i = 0; i < diff; i++) {
      if (mul_by_10(&temp) != S21_OK) {
        overflow = 1;
        break;
      }
    }
    if (!overflow) {
      *value_2 = temp;
      set_scale(value_2, scale1);
    } else {
      my_big_decimal big_v1 = decimal_to_big(*value_1);
      int diff_reverse = scale1 - scale2;
      int remainder = 0;
      for (int i = 0; i < diff_reverse; i++) {
        remainder = div_by_10_big(&big_v1);
      }
      bank_rounding(&big_v1, remainder);
      if (!is_overflow_big(big_v1)) {
        big_to_decimal(big_v1, value_1);
        set_scale(value_1, scale2);
      }
    }
  }
}

my_big_decimal decimal_to_big(my_decimal value) {
  my_big_decimal res = {0};
  for (int i = 0; i < 3; i++) res.bits[i] = value.bits[i];
  return res;
}

void big_to_decimal(my_big_decimal src, my_decimal *dst) {
  init_decimal(dst);
  for (int i = 0; i < 3; i++) dst->bits[i] = src.bits[i];
}

int compare_bits(my_decimal value_1, my_decimal value_2) {
  for (int i = 2; i >= 0; i--) {
    unsigned int a = (unsigned int)value_1.bits[i];
    unsigned int b = (unsigned int)value_2.bits[i];
    if (a > b) return 1;
    if (a < b) return -1;
  }
  return 0;
}

int add_bits(my_decimal *result, my_decimal value_1, my_decimal value_2) {
  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long sum = (unsigned long long)value_1.bits[i] +
                             (unsigned long long)value_2.bits[i] + carry;
    result->bits[i] = (int)(sum & 0xFFFFFFFF);
    carry = sum >> 32;
  }
  return carry != 0;
}

int sub_bits(my_decimal *result, my_decimal value_1, my_decimal value_2) {
  long long borrow = 0;
  for (int i = 0; i < 3; i++) {
    long long diff = (long long)(unsigned int)value_1.bits[i] -
                     (long long)(unsigned int)value_2.bits[i] - borrow;
    if (diff < 0) {
      diff += 0x100000000LL;
      borrow = 1;
    } else {
      borrow = 0;
    }
    result->bits[i] = (int)diff;
  }
  return borrow != 0;
}

int get_bit(my_decimal value, int index) {
  int array_index = index / 32;
  int bit_index = index % 32;
  return (value.bits[array_index] >> bit_index) & 1;
}

// сдвигаем мантиссу влево на 1 бит
int shift_left(my_decimal *value) {
  int carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long temp = (unsigned long long)value->bits[i] << 1;
    temp += carry;
    value->bits[i] = (unsigned int)(temp & 0xFFFFFFFF);
    carry = (temp >> 32) > 0;
  }
  return carry;
}

int is_full_value_zero(my_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}

void div_integer_mantissa(my_decimal dividend, my_decimal divisor,
                          my_decimal *quotient, my_decimal *remainder) {
  init_decimal(quotient);
  init_decimal(remainder);

  for (int i = 95; i >= 0; i--) {
    shift_left(remainder);

    if (get_bit(dividend, i)) {
      remainder->bits[0] |= 1;
    }

    if (compare_bits(*remainder, divisor) >= 0) {
      sub_bits(remainder, *remainder, divisor);
      int q_index = i / 32;
      int q_bit = i % 32;
      quotient->bits[q_index] |= (1 << q_bit);
    }
  }
}

int mul_by_10(my_decimal *value) {
  my_decimal temp = *value;

  // x * 10 = (x * 8) + (x * 2) = (x << 3) + (x << 1)
  my_decimal ten;
  init_decimal(&ten);
  ten.bits[0] = 10;
  return_code rc = S21_OK;
  my_decimal x2 = temp;
  if (shift_left(&x2)) rc = S21_TOO_LARGE;

  my_decimal x8 = x2;
  if (rc == S21_OK && shift_left(&x8)) rc = S21_TOO_LARGE;
  if (rc == S21_OK && shift_left(&x8)) rc = S21_TOO_LARGE;

  if (rc == S21_OK && add_bits(value, x2, x8))
    rc = S21_TOO_LARGE;  // x10 = x2 + x8

  return rc;
}

void add_big(my_big_decimal value_1, my_big_decimal value_2,
             my_big_decimal *result) {
  unsigned long long carry = 0;
  for (int i = 0; i < 7; i++) {
    unsigned long long sum = (unsigned long long)value_1.bits[i] +
                             (unsigned long long)value_2.bits[i] + carry;
    result->bits[i] = (unsigned int)(sum & 0xFFFFFFFF);
    carry = sum >> 32;
  }
}

void shift_left_big(my_big_decimal *dst, int shift) {
  if (shift == 0) return;
  int words_shift = shift / 32;
  int bits_shift = shift % 32;

  if (words_shift > 0) {
    for (int i = 6; i >= words_shift; i--) {
      dst->bits[i] = dst->bits[i - words_shift];
    }
    for (int i = 0; i < words_shift; i++) {
      dst->bits[i] = 0;
    }
  }

  if (bits_shift > 0) {
    unsigned int carry = 0;
    for (int i = 0; i < 7; i++) {
      unsigned long long temp =
          ((unsigned long long)dst->bits[i] << bits_shift) | carry;
      dst->bits[i] = (unsigned int)(temp & 0xFFFFFFFF);
      carry = (unsigned int)(temp >> 32);
    }
  }
}

// результат может занимать до 192 бит
my_big_decimal mul_mantissa(my_decimal value_1, my_decimal value_2) {
  my_big_decimal res = {0};
  my_big_decimal v1 = {0};

  for (int i = 0; i < 3; i++) v1.bits[i] = value_1.bits[i];

  for (int i = 0; i < 96; i++) {
    if (get_bit(value_2, i)) {
      my_big_decimal temp = v1;
      shift_left_big(&temp, i);
      add_big(res, temp, &res);
    }
  }
  return res;
}

int div_by_10_big(my_big_decimal *value) {
  unsigned long long remainder = 0;
  for (int i = 6; i >= 0; i--) {
    unsigned long long current = value->bits[i] + (remainder << 32);
    value->bits[i] = (unsigned int)(current / 10);
    remainder = current % 10;
  }
  return (int)remainder;
}

int is_overflow_big(my_big_decimal value) {
  return (value.bits[3] | value.bits[4] | value.bits[5] | value.bits[6]) != 0;
}

void add_one_big(my_big_decimal *value) {
  unsigned long long carry = 1;
  for (int i = 0; i < 7 && carry; i++) {
    unsigned long long sum = (unsigned long long)value->bits[i] + carry;
    value->bits[i] = (unsigned int)(sum & 0xFFFFFFFF);
    carry = sum >> 32;
  }
}

void bank_rounding(my_big_decimal *value, int remainder) {
  if (remainder > 5 || (remainder == 5 && (value->bits[0] & 1))) {
    add_one_big(value);
  }
}