#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal num_1, s21_decimal num_2) {
  return s21_is_equal(num_1, num_2) ? 0 : 1;
}
