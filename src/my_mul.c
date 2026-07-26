#include "my_decimal.h"

int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result) {
  if (!result) return S21_DEREFERENCING_NULL_POINTER_ATTEMPT;

  for (int i = 0; i < 4; i++) result->bits[i] = 0;

  int sign_result = get_sign(value_1) ^ get_sign(value_2);
  int scale_result = get_scale(value_1) + get_scale(value_2);

  my_big_decimal big_res = mul_mantissa(value_1, value_2);
  int remainder = 0;
  while (scale_result > 28 || (scale_result > 0 && is_overflow_big(big_res))) {
    remainder = div_by_10_big(&big_res);
    scale_result--;

    if (scale_result > 28 || (scale_result > 0 && is_overflow_big(big_res))) {
    } else {
      bank_rounding(&big_res, remainder);
      if (is_overflow_big(big_res) && scale_result > 0) {
        remainder = div_by_10_big(&big_res);
        scale_result--;
        bank_rounding(&big_res, remainder);
      }
    }
  }

  if (is_overflow_big(big_res)) {
    for (int i = 0; i < 4; i++) result->bits[i] = 0;

    if (sign_result == 1) return S21_TOO_SMALL;
    return S21_TOO_LARGE;
  }

  for (int i = 0; i < 3; i++) {
    result->bits[i] = big_res.bits[i];
  }

  result->bits[3] = 0;
  set_scale(result, scale_result);
  set_sign(result, sign_result);

  return S21_OK;
}
