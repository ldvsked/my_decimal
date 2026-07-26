#include "my_decimal.h"

int my_truncate(my_decimal value, my_decimal *result) {
  if (!result) return 1;
  int scale = get_scale(value);
  my_decimal temp = value;

  my_decimal ten;
  init_decimal(&ten);
  ten.bits[0] = 10;

  for (int i = 0; i < scale; i++) {
    my_decimal quotient, remainder;
    div_integer_mantissa(temp, ten, &quotient, &remainder);

    temp = quotient;
  }
  *result = temp;

  int sign = get_sign(value);
  set_sign(result, sign);
  set_scale(result, 0);

  return S21_OK;
}
