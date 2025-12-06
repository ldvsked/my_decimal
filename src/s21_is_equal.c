#include "comparison_operators.h"

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
    s21_decimal n1 = normalize_decimal(num1);
    s21_decimal n2 = normalize_decimal(num2);

    return (get_sign(n1) == get_sign(n2)) &&
           (get_degree(n1) == get_degree(n2)) &&
           (n1.bits[0] == n2.bits[0]) &&
           (n1.bits[1] == n2.bits[1]) &&
           (n1.bits[2] == n2.bits[2]);
}