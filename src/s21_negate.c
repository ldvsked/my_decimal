#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;

  *result = value;

  int sign = get_sign(value);
  set_sign(result, !sign);

  return S21_OK;
}
