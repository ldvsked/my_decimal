#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (!result)
    return S21_DEREFERENCING_NULL_POINTER_ATTEMPT;

  *result = value;

  int sign = get_sign(value);
  set_sign(result, !sign);

  return S21_OK;
}
