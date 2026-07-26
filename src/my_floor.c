#include "my_decimal.h"

int my_floor(my_decimal value, my_decimal* result) {
  if (!result) return 1;
  int return_code = 0;
  if (my_truncate(value, result) != 0) {
    return_code = 1;
  }

  int sign = get_sign(value);

  if (!return_code && sign == 1 && my_is_not_equal(value, *result)) {
    my_decimal one = {{1, 0, 0, 0}};
    my_sub(*result, one, result);
  }

  return return_code;
}
