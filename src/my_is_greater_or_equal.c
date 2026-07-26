#include "my_decimal.h"

int my_is_greater_or_equal(my_decimal num_1, my_decimal num_2) {
  return (my_is_greater(num_1, num_2) || my_is_equal(num_1, num_2));
}
