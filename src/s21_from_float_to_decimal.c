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

  // вычисляем количество цифр в целой части
  int int_digits = 0;
  double tmp = src_abs;
  if (!flag && tmp >= 1.0) {
    while (tmp >= 1.0) {
      tmp /= 10.0;
      int_digits++;
    }
  }

  int scale = 0;
  int max_scale = 7 - int_digits;  // максимальный scale
  if (max_scale < 0) max_scale = 0;

  const double EPS = 1e-9;
  while (!flag && scale < max_scale && fabs(src_abs - round(src_abs)) > EPS) {
    double before = src_abs;
    src_abs *= 10.0;

    if (before < 1.0 && src_abs < 1.0) {
      max_scale++;  // расширяем scale, потому что значащих цифр не прибыло
    }

    scale++;
  }

  if (!flag) {
    // Банковское округление: округляем к ближайшему чётному целому
    double int_part;
    double frac_part = modf(src_abs, &int_part);

    // применяем банковское округление
    if (frac_part == 0.5) {
      // если нечетное → +1
      if (fmod(int_part, 2.0) != 0.0) int_part += 1.0;
    } else {
      int_part = (double)(float)round(src_abs);
    }

    // Разбиваем число на 32-битные слова без переполнения
    double temp = int_part;
    dst->bits[0] = (unsigned int)fmod(temp, 4294967296.0);
    temp = floor(temp / 4294967296.0);
    dst->bits[1] = (unsigned int)fmod(temp, 4294967296.0);
    temp = floor(temp / 4294967296.0);
    dst->bits[2] = (unsigned int)fmod(temp, 4294967296.0);
  }

  if (!flag && sign) {
    dst->bits[3] = 1u << 31;
  }
  if (!flag) {
    dst->bits[3] = (dst->bits[3]) | (scale << 16);
  }

  return flag;
}