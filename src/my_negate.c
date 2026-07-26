#include "my_decimal.h"

int my_negate(my_decimal value, my_decimal *result) {
  if (!result) return 1;

  *result = value;

  int sign = get_sign(value);
  set_sign(result, !sign);

  return S21_OK;
}
