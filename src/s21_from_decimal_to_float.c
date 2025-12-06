#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  // макс флот 3.4e38 = (2 - 2^(-23)) ^ 2^127 = 2 ^ 128
  // макс decimal 7.9e28 = 2^96 - 1
  float dst_abs =
      (src.bits[2] * pow(2, 64) + src.bits[1] * pow(2, 32) + src.bits[0]);
  int sign = pow(-1, (src.bits[3] >> 31 & 1));
  int scale = (src.bits[3] << 1) >> 17;
  *dst = sign * dst_abs / pow(10, scale);
  return 0;
}
