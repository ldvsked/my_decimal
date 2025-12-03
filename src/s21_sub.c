#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);
void normalize_scale(s21_decimal* v1, s21_decimal* v2);
int add_bits(s21_decimal* res, s21_decimal v1, s21_decimal v2);
int sub_bits(s21_decimal* res, s21_decimal v1, s21_decimal v2);
int compare_bits(s21_decimal v1, s21_decimal v2);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  // if (result == NULL) {
  //     return 0;
  // }
  init_decimal(result);

  s21_decimal negated_value_2;
  s21_negate(value_2, &negated_value_2);

  return s21_add(value_1, negated_value_2, result);
}

int s21_negate(s21_decimal value, s21_decimal* result) {
  if (result == NULL) return 1;
  *result = value;
  set_sign(result, !get_sign(value));
  return 0;
}
