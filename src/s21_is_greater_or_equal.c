#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal num_1, s21_decimal num_2) {
  return (s21_is_greater(num_1, num_2) || s21_is_equal(num_1, num_2));
}
