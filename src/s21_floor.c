#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal* result) {
  if (!result) return 1;
  int return_code = 0;
  if (s21_truncate(value, result) != 0) {
    return_code = 1;
  }

  int sign = get_sign(value);

  if (!return_code && sign == 1 && s21_is_not_equal(value, *result)) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_sub(*result, one, result);
  }

  return return_code;
}
