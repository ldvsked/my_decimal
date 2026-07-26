#include "my_decimal.h"

int my_is_not_equal(my_decimal num_1, my_decimal num_2) {
  return my_is_equal(num_1, num_2) ? 0 : 1;
}
