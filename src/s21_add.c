#include "s21_decimal.h"


int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (result == NULL) {
      return S21_DEREFERENCING_NULL_POINTER_ATTEMPT;
  }
  return_code rc = S21_OK;
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
      rc = S21_TOO_LARGE;
    } else {
      rc = S21_TOO_SMALL;
    }
  }

  return rc;
}
