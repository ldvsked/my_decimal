#include "s21_decimal.h"


s21_decimal normalize_decimal(s21_decimal num);

int divide_by_10(unsigned int bits[3]);

int multiply_by_10(unsigned int value[3]);

int align_decimal_scales(s21_decimal value_1, s21_decimal value_2, s21_decimal* out_1, s21_decimal* out_2);
