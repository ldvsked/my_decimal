#include "my_decimal.h"

int my_round(my_decimal value, my_decimal *result) {
  if (!result) return 1;
  my_decimal integer_part;
  int return_code = 0;
  if (my_truncate(value, &integer_part) != 0) {
    return_code = 1;
  }

  my_decimal fractional_part;
  my_sub(value, integer_part, &fractional_part);

  int sign = get_sign(value);
  set_sign(&fractional_part, 0);
  my_decimal half = {{5, 0, 0, 0x00010000}};  // 0.5 (5 * 10^-1)

  if (!return_code && my_is_greater_or_equal(fractional_part, half)) {
    my_decimal one = {{1, 0, 0, 0}};
    if (sign == 0) {
      my_add(integer_part, one, result);
    } else {
      my_sub(integer_part, one, result);
    }
  } else {
    *result = integer_part;
  }

  return return_code;
}
