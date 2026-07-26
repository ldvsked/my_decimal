#include "my_decimal.h"

int my_is_equal(my_decimal num1, my_decimal num2) {
  my_decimal n1 = normalize_decimal(num1);
  my_decimal n2 = normalize_decimal(num2);

  return (get_sign(n1) == get_sign(n2)) && (get_degree(n1) == get_degree(n2)) &&
         (n1.bits[0] == n2.bits[0]) && (n1.bits[1] == n2.bits[1]) &&
         (n1.bits[2] == n2.bits[2]);
}