#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;
  s21_decimal integer_part;
  int return_code = 0;
  if (s21_truncate(value, &integer_part) != 0) {
    return_code = 1;
  }

  s21_decimal fractional_part;
  s21_sub(value, integer_part, &fractional_part);

  int sign = get_sign(value);
  set_sign(&fractional_part, 0);
  s21_decimal half = {{5, 0, 0, 0x00010000}};  // 0.5 (5 * 10^-1)

  if (!return_code && s21_is_greater_or_equal(fractional_part, half)) {
    s21_decimal one = {{1, 0, 0, 0}};
    if (sign == 0) {
      s21_add(integer_part, one, result);
    } else {
      s21_sub(integer_part, one, result);
    }
  } else {
    *result = integer_part;
  }

  return return_code;
}
