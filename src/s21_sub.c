#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (!result) return S21_DEREFERENCING_NULL_POINTER_ATTEMPT;
  init_decimal(result);
  s21_decimal negated_value_2 = value_2;
  int sign = get_sign(negated_value_2);
  set_sign(&negated_value_2, !sign);
  return s21_add(value_1, negated_value_2, result);
}
