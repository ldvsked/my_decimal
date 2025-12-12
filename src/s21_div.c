#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return S21_DEREFERENCING_NULL_POINTER_ATTEMPT;
  if (is_full_value_zero(value_2)) return S21_DIV_BY_ZERO;

  init_decimal(result);
  return_code code = S21_OK;

  int sign1 = get_sign(value_1);
  int sign2 = get_sign(value_2);
  int res_sign = sign1 ^ sign2;

  int scale1 = get_scale(value_1);
  int scale2 = get_scale(value_2);

  s21_decimal man1 = value_1;
  s21_decimal man2 = value_2;
  man1.bits[3] = 0;
  man2.bits[3] = 0;

  s21_decimal temp_res;
  init_decimal(&temp_res);
  s21_decimal remainder;

  div_integer_mantissa(man1, man2, &temp_res, &remainder);
  int res_scale = scale1 - scale2;

  // если делитель был меньше делимого по степени
  while (res_scale < 0 && code == S21_OK) {
    if (mul_by_10(&temp_res)) {
      code = res_sign ? S21_TOO_SMALL : S21_TOO_LARGE;
    }
    res_scale++;
  }

  while (!is_full_value_zero(remainder) && res_scale < 28 && code == S21_OK) {
    s21_decimal next_val = temp_res;
    if (mul_by_10(&next_val)) break;

    s21_decimal rem_x10 = remainder;
    mul_by_10(&rem_x10);

    s21_decimal part_q, part_r;
    div_integer_mantissa(rem_x10, man2, &part_q, &part_r);

    temp_res = next_val;
    add_bits(&temp_res, temp_res, part_q);
    remainder = part_r;

    res_scale++;
  }

  if (code == S21_OK) {
    s21_decimal difference = {0};

    if (!is_full_value_zero(remainder)) {
      sub_bits(&difference, man2, remainder);
      int needs_rounding = 0;

      difference.bits[3] = 0;
      remainder.bits[3] = 0;

      if (s21_is_greater(remainder, difference)) {
        needs_rounding = 1;
      } else if (s21_is_equal(remainder, difference)) {
        if (get_bit(temp_res, 0)) {
          needs_rounding = 1;
        }
      }

      if (needs_rounding) {
        s21_decimal one = {{1, 0, 0, 0}};
        if (add_bits(&temp_res, temp_res, one)) {
          code = res_sign ? S21_TOO_SMALL : S21_TOO_LARGE;
        }
      }
    }
  }

  if (code == S21_OK) {
    set_scale(&temp_res, res_scale);
    set_sign(&temp_res, res_sign);
    *result = temp_res;
  }

  return code;
}
