#include "s21_decimal.h"

void print_binary(int num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
    if (i % 8 == 0) printf("|");
  }
  printf("\n");
}

void print_decimal_binary(s21_decimal number) {
  for (int i = 0; i < 4; i++) {
    printf("%d :", i);
    print_binary(number.bits[i]);
    printf("---------------------------------------\n");
  }
}

void set_degree(s21_decimal *ch, int exp) {
  ch->bits[3] = (ch->bits[3] & 0x8000FFFF) | (exp << 16);
}

int get_degree(const s21_decimal ch) { return (ch.bits[3] >> 16) & 255; }

int is_zero(const unsigned int bits[3]) {
  return bits[0] == 0 && bits[1] == 0 && bits[2] == 0;
}

void print_decimal_normal(const s21_decimal numb) {
  int sign = get_sign(numb);
  int scale = get_degree(numb);
  unsigned int bits[3] = {numb.bits[0], numb.bits[1], numb.bits[2]};
  if (is_zero(bits)) {
    printf("0\n");
    return;
  }
  if (sign) printf("-");

  char digits[100] = {0};
  int digit_count = 0;

  while (!is_zero(bits)) {
    int digit = divide_by_10(bits);
    digits[digit_count++] = '0' + digit;
  }

  if (scale == 0) {
    for (int i = digit_count - 1; i >= 0; i--) {
      printf("%c", digits[i]);
    }
  } else {
    if (digit_count <= scale) {
      printf("0.");
      for (int i = 0; i < scale - digit_count; i++) {
        printf("0");
      }
      for (int i = digit_count - 1; i >= 0; i--) {
        printf("%c", digits[i]);
      }
    } else {
      for (int i = digit_count - 1; i >= 0; i--) {
        printf("%c", digits[i]);
        if (i == scale) {
          printf(".");
        }
      }
    }
  }
  printf("\n");
}

s21_decimal normalize_decimal(s21_decimal num) {
  s21_decimal result = {{0}};

  if (is_zero(num.bits)) {
  } else {
    unsigned int mantissa[3] = {num.bits[0], num.bits[1], num.bits[2]};
    int scale = get_degree(num);
    int sign = get_sign(num);
    int finished = 0;

    while (scale > 0 && !finished) {
      unsigned int backup[3] = {mantissa[0], mantissa[1], mantissa[2]};
      int last_digit = divide_by_10(mantissa);
      if (last_digit == 0) {
        scale--;
        if (is_zero(mantissa)) {
          finished = 1;
        }
      } else {
        mantissa[0] = backup[0];
        mantissa[1] = backup[1];
        mantissa[2] = backup[2];
        finished = 1;
      }
    }
    result.bits[0] = mantissa[0];
    result.bits[1] = mantissa[1];
    result.bits[2] = mantissa[2];
    set_degree(&result, scale);
    set_sign(&result, sign);
  }
  return result;
}

int divide_by_10(unsigned int bits[3]) {
  unsigned long long remainder = 0;
  for (int i = 2; i >= 0; i--) {
    unsigned long long temp = (remainder << 32) | bits[i];
    bits[i] = temp / 10;
    remainder = temp % 10;
  }
  return (int)remainder;
}

int multiply_by_10(unsigned int value[3]) {
  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long temp = (unsigned long long)value[i] * 10ULL + carry;
    value[i] = (unsigned int)(temp & 0xFFFFFFFFULL);
    carry = temp >> 32;
  }
  return (carry == 0);
}

// приведение к общему масштабу
int align_decimal_scales(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *out_1, s21_decimal *out_2) {
  int res = 1;
  *out_1 = value_1;
  *out_2 = value_2;
  int scale1 = get_degree(value_1);
  int scale2 = get_degree(value_2);

  if (scale1 != scale2) {
    int diff = (scale1 > scale2) ? (scale1 - scale2) : (scale2 - scale1);
    s21_decimal *to_scale = (scale1 < scale2) ? out_1 : out_2;
    for (int i = 0; i < diff && res; i++) {
      if (!multiply_by_10(to_scale->bits)) {
        res = 0;
      }
    }
    if (res) {
      if (scale1 < scale2) {
        set_degree(out_1, scale2);
      } else {
        set_degree(out_2, scale1);
      }
    }
  }
  return res;
}