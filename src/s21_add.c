#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (!result) return S21_DEREFERENCING_NULL_POINTER_ATTEMPT;
  return_code rc = S21_OK;
  init_decimal(result);
  int sign1 = get_sign(value_1);
  int sign2 = get_sign(value_2);
  s21_decimal v1 = value_1;
  s21_decimal v2 = value_2;
  normalize_scale(&v1, &v2);
  int scale = get_scale(v1);
  if (sign1 == sign2) {
    s21_big_decimal b1 = {0};
    s21_big_decimal b2 = {0};
    s21_big_decimal bres = {0};
    b1.bits[0] = v1.bits[0];
    b1.bits[1] = v1.bits[1];
    b1.bits[2] = v1.bits[2];
    b2.bits[0] = v2.bits[0];
    b2.bits[1] = v2.bits[1];
    b2.bits[2] = v2.bits[2];
    add_big(b1, b2, &bres);
    int cur_scale = scale;
    while (is_overflow_big(bres) && cur_scale > 0) {
      int rem = div_by_10_big(&bres);
      bank_rounding(&bres, rem);
      cur_scale--;
    }
    if (is_overflow_big(bres)) {
      if (sign1) {
        rc = S21_TOO_SMALL;
      } else {
        rc = S21_TOO_LARGE;
      }
    }
    if (!rc) {
      result->bits[0] = bres.bits[0];
      result->bits[1] = bres.bits[1];
      result->bits[2] = bres.bits[2];
      set_scale(result, cur_scale);
      set_sign(result, sign1);
    }
  } else {
    int cmp = compare_bits(v1, v2);
    if (cmp == 0) {
      init_decimal(result);
    } else {
      s21_decimal tmp_res;
      init_decimal(&tmp_res);
      if (cmp > 0) {
        sub_bits(&tmp_res, v1, v2);
        set_sign(&tmp_res, sign1);
      } else {
        sub_bits(&tmp_res, v2, v1);
        set_sign(&tmp_res, sign2);
      }
      set_scale(&tmp_res, scale);
      *result = tmp_res;
    }
  }
  return rc;
}
