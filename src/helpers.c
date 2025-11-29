#include "s21_decimal.h"

int get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }

void set_sign(s21_decimal* value, int sign) {
  if (sign) {
    value->bits[3] |= (1 << 31);
  } else {
    value->bits[3] &= ~(1 << 31);
  }
}

int get_scale(s21_decimal value) { return (value.bits[3] >> 16) & 0xFF; }

void set_scale(s21_decimal* value, int scale) {
  value->bits[3] &= 0x80000000;
  value->bits[3] |= (scale << 16);
}

void normalize_scale(s21_decimal* value_1, s21_decimal* value_2) {
  int scale1 = get_scale(*value_1);
  int scale2 = get_scale(*value_2);
  if (scale1 == scale2) return;
  // приводим к большей степени умножением на 10
  s21_decimal* smaller_scale = (scale1 < scale2) ? value_1 : value_2;
  int diff = (scale1 < scale2) ? (scale2 - scale1) : (scale1 - scale2);
  for (int i = 0; i < diff; i++) {
    unsigned long long carry = 0;
    for (int j = 0; j < 3; j++) {
      unsigned long long temp =
          (unsigned long long)(unsigned int)smaller_scale->bits[j] * 10ULL +
          carry;
      smaller_scale->bits[j] = (int)(temp & 0xFFFFFFFF);
      carry = temp >> 32;
    }
  }
  if (scale1 < scale2) {
    set_scale(value_1, scale2);
  } else {
    set_scale(value_2, scale1);
  }
}