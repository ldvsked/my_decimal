#include "my_decimal.h"

int my_sub(my_decimal value_1, my_decimal value_2, my_decimal* result) {
  if (!result) return S21_DEREFERENCING_NULL_POINTER_ATTEMPT;
  init_decimal(result);
  my_decimal negated_value_2 = value_2;
  int sign = get_sign(negated_value_2);
  set_sign(&negated_value_2, !sign);
  return my_add(value_1, negated_value_2, result);
}
