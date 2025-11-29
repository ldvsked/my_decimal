#include "s21_decimal.h"

#define S21_OK 0
#define S21_TOO_LARGE 1
#define S21_TOO_SMALL 2
#define S21_DIV_BY_ZERO 3

int add_bits(s21_decimal* result, s21_decimal value_1, s21_decimal value_2) {
  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long sum = (unsigned long long)value_1.bits[i] +
                             (unsigned long long)value_2.bits[i] + carry;
    result->bits[i] = (int)(sum & 0xFFFFFFFF);
    carry = sum >> 32;
  }
  return carry != 0;
}

int sub_bits(s21_decimal* result, s21_decimal value_1, s21_decimal value_2) {
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

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int err = 0;
  init_decimal(result);
  int sign1 = get_sign(value_1);
  int sign2 = get_sign(value_2);
  normalize_scale(&value_1, &value_2);
  int result_scale = get_scale(value_1);
  int overflow = 0;
  if (sign1 == sign2) {
    overflow = add_bits(result, value_1, value_2);
    set_sign(result, sign1);
  } else {
    int cmp = compare_bits(value_1, value_2);
    if (cmp >= 0) {
      sub_bits(result, value_1, value_2);
      set_sign(result, sign1);
    } else {
      sub_bits(result, value_2, value_1);
      set_sign(result, sign2);
    }
  }

  set_scale(result, result_scale);

  if (overflow) {
    if (get_sign(*result) == 0) {
      err = 1;
    } else {
      err = 2;
    }
  }

  return err;
}
