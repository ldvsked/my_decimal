#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result)
    return S21_DEREFERENCING_NULL_POINTER_ATTEMPT;
  int scale = get_scale(value);
  s21_decimal temp = value;

  s21_decimal ten;
  init_decimal(&ten);
  ten.bits[0] = 10;

  for (int i = 0; i < scale; i++) {
    s21_decimal quotient, remainder;
    div_integer_mantissa(temp, ten, &quotient, &remainder);

    temp = quotient;
  }
  *result = temp;

  int sign = get_sign(value);
  set_sign(result, sign);
  set_scale(result, 0);

  return S21_OK;
}
