#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = 0;
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;

  int sign = (src < 0);
  double src_abs = fabs((double)src);  // для большей точности

  if (src_abs > 0 && src_abs < 1e-28) {
    flag = 1;
  }

  if (src_abs > 79228162514264337593543950335.0 || isinf(src)) {
    flag = 1;
  }

  if (!flag) {
    char buffer[256];
    sprintf(buffer, "%.7g", src_abs);  // вот это до 7 знаков округляет
    src_abs = atof(buffer);
  }

  int scale = 0;
  while (!flag && scale < 28 && floor(src_abs) != src_abs) {
    scale += 1;
    src_abs *= 10;
  }
  // printf("%d\n", (int)src_abs);
  // printf("%d\n", scale);

  if (!flag) {
    // максимум у флота 3.4e38
    unsigned long long int_value = (unsigned long long)src_abs;

    dst->bits[0] = (unsigned int)int_value;
    dst->bits[1] = (unsigned int)(int_value >> 32);
  }

  if (!flag && sign) {
    dst->bits[3] = 1u << 31;
  }
  if (!flag) {
    dst->bits[3] = (dst->bits[3]) | (scale << 16);
  }

  return flag;
}