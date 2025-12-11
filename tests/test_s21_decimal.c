#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/s21_decimal.h"

START_TEST(test_s21_add_positive_numbers) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(100, &val1);
  s21_from_int_to_decimal(50, &val2);

  int status = s21_add(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 150);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_add_negative_numbers) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(-100, &val1);
  s21_from_int_to_decimal(-50, &val2);

  int status = s21_add(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 150);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_s21_add_mixed_signs) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(100, &val1);
  s21_from_int_to_decimal(-50, &val2);

  int status = s21_add(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_add_with_scale) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(105, &val1);
  set_scale(&val1, 1);
  s21_from_int_to_decimal(53, &val2);
  set_scale(&val2, 1);

  int status = s21_add(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 158);
  ck_assert_int_eq(get_scale(result), 1);
}
END_TEST

START_TEST(test_s21_add_zero) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(100, &val1);
  s21_from_int_to_decimal(0, &val2);

  int status = s21_add(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_s21_add_max_int) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(2147483647, &val1);
  s21_from_int_to_decimal(1, &val2);

  int status = s21_add(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2147483648U);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_21_add_min_max) {
  s21_decimal max_dec = {{-1, -1, -1, 0}};
  s21_decimal min_dec = {{-1, -1, -1, 0x80000000}};
  s21_decimal result;

  int status = s21_add(max_dec, min_dec, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_21_add_min_min) {
  s21_decimal min_dec = {{-1, -1, -1, 0x80000000}};
  s21_decimal result;

  int status = s21_add(min_dec, min_dec, &result);

  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_21_add_max_max) {
  s21_decimal max_dec = {{-1, -1, -1, 0}};
  s21_decimal result;

  int status = s21_add(max_dec, max_dec, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_21_add_max_min) {
  s21_decimal max_dec = {{-1, -1, -1, 0}};
  s21_decimal min_dec = {{-1, -1, -1, 0x80000000}};
  s21_decimal result;

  int status = s21_add(max_dec, min_dec, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_21_add_null_pointer) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  int status = s21_add(val1, val2, NULL);

  ck_assert_int_eq(status, 4);
}
END_TEST

START_TEST(test_s21_sub_positive_numbers) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(100, &val1);
  s21_from_int_to_decimal(50, &val2);

  int status = s21_sub(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_sub_negative_numbers) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(-100, &val1);
  s21_from_int_to_decimal(-50, &val2);

  int status = s21_sub(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_s21_sub_mixed_signs) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(100, &val1);
  s21_from_int_to_decimal(-50, &val2);

  int status = s21_sub(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 150);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_sub_with_scale) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(105, &val1);
  set_scale(&val1, 1);
  s21_from_int_to_decimal(5, &val2);
  set_scale(&val2, 1);

  int status = s21_sub(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(get_scale(result), 1);
  // ck_assert_int_eq(result.bits[0], 10);
  // ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_s21_sub_zero) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(100, &val1);
  s21_from_int_to_decimal(0, &val2);

  int status = s21_sub(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 100);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_21_sub_min_max) {
  s21_decimal max_dec = {{-1, -1, -1, 0}};
  s21_decimal min_dec = {{-1, -1, -1, 0x80000000}};
  s21_decimal result;

  int status = s21_sub(min_dec, max_dec, &result);

  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_21_sub_min_min) {
  s21_decimal min_dec = {{-1, -1, -1, 0x80000000}};
  s21_decimal result;

  int status = s21_sub(min_dec, min_dec, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_21_sub_max_max) {
  s21_decimal max_dec = {{-1, -1, -1, 0}};
  s21_decimal result;

  int status = s21_sub(max_dec, max_dec, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_21_sub_max_min) {
  s21_decimal max_dec = {{-1, -1, -1, 0}};
  s21_decimal min_dec = {{-1, -1, -1, 0x80000000}};
  s21_decimal result;

  int status = s21_sub(max_dec, min_dec, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_21_sub_null_pointer) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  int status = s21_sub(val1, val2, NULL);

  ck_assert_int_eq(status, 4);
}
END_TEST

START_TEST(test_s21_mul_null_ptr) {
  s21_decimal val1 = {0}, val2 = {0};
  int status = s21_mul(val1, val2, NULL);
  ck_assert_int_eq(status, S21_DEREFERENCING_NULL_POINTER_ATTEMPT);
}
END_TEST

START_TEST(test_s21_mul_positive_numbers) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(10, &val1);
  s21_from_int_to_decimal(5, &val2);

  // 10 * 5 = 50
  int status = s21_mul(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_s21_mul_negative_positive) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(-10, &val1);
  s21_from_int_to_decimal(5, &val2);

  // -10 * 5 = -50
  int status = s21_mul(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_s21_mul_overflow_recoverable) {
  s21_decimal val1, val2, result;

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  val1.bits[3] = 0;

  s21_from_int_to_decimal(2, &val2);

  set_scale(&val1, 1);

  int status = s21_mul(val1, val2, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_ne(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_mul_huge_scale_rounding) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(15, &val1);
  set_scale(&val1, 20);

  s21_from_int_to_decimal(1, &val2);
  set_scale(&val2, 15);

  int status = s21_mul(val1, val2, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_s21_mul_big_numbers) {
  s21_decimal val1, val2, result;
  init_decimal(&val1);
  init_decimal(&val2);

  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[0] = 2;

  // (2^32 - 1) * 2 = 2^33 - 2
  int status = s21_mul(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0xFFFFFFFE);
  ck_assert_int_eq(result.bits[1], 1);
}
END_TEST

START_TEST(test_s21_mul_large_shift) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(2, &val1);

  init_decimal(&val2);
  val2.bits[2] = 1;  // 2^64

  // result = 2 * 2^64 = 2^65.
  int status = s21_mul(val1, val2, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(result.bits[2], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_mul_too_small) {
  s21_decimal val1, val2, result;
  // val1 = -MAX
  init_decimal(&val1);
  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_sign(&val1, 1);

  s21_from_int_to_decimal(2, &val2);

  int status = s21_mul(val1, val2, &result);

  ck_assert_int_eq(status, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_div_null_ptr) {
  s21_decimal val1 = {0}, val2 = {0};
  int status = s21_div(val1, val2, NULL);
  ck_assert_int_eq(status, S21_DEREFERENCING_NULL_POINTER_ATTEMPT);
}
END_TEST

START_TEST(test_s21_div_simple) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(10, &val1);
  s21_from_int_to_decimal(2, &val2);

  int status = s21_div(val1, val2, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_div_fractional) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(5, &val1);
  s21_from_int_to_decimal(2, &val2);

  int status = s21_div(val1, val2, &result);
  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(result.bits[0], 25);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_div_negative) {
  s21_decimal val1, val2, result;
  // -10 / 2 = -5
  s21_from_int_to_decimal(-10, &val1);
  s21_from_int_to_decimal(2, &val2);

  int status = s21_div(val1, val2, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_s21_div_by_zero) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(10, &val1);
  s21_from_int_to_decimal(0, &val2);

  int status = s21_div(val1, val2, &result);

  ck_assert_int_eq(status, S21_DIV_BY_ZERO);
}
END_TEST

START_TEST(test_s21_div_small_result) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(1, &val1);
  s21_from_int_to_decimal(4, &val2);

  int status = s21_div(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 25);
  ck_assert_int_eq(get_scale(result), 2);
}
END_TEST

START_TEST(test_s21_div_complex) {
  s21_decimal val1, val2, result;
  // 1 / 3 = 0.333333...
  // функция должна остановиться на scale 28 или переполнении мантиссы
  s21_from_int_to_decimal(1, &val1);
  s21_from_int_to_decimal(3, &val2);

  int status = s21_div(val1, val2, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_ge(get_scale(result), 1);
}
END_TEST

START_TEST(test_s21_div_mantissa_overflow_break) {
  s21_decimal val1, val2, result;
  // val1 = MAX_UINT96
  init_decimal(&val1);
  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  // val2 = 10
  s21_from_int_to_decimal(10, &val2);
  int status = s21_div(val1, val2, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_ne(result.bits[0], 0);
}
END_TEST

TCase *create_arithmetic_tcase(void) {
  TCase *tc = tcase_create("arithmetic");
  tcase_add_test(tc, test_s21_add_positive_numbers);
  tcase_add_test(tc, test_s21_add_negative_numbers);
  tcase_add_test(tc, test_s21_add_mixed_signs);
  tcase_add_test(tc, test_s21_add_with_scale);
  tcase_add_test(tc, test_s21_add_zero);
  tcase_add_test(tc, test_s21_add_max_int);
  tcase_add_test(tc, test_21_add_min_max);
  tcase_add_test(tc, test_21_add_min_min);
  tcase_add_test(tc, test_21_add_max_max);
  tcase_add_test(tc, test_21_add_max_min);
  tcase_add_test(tc, test_21_add_null_pointer);

  tcase_add_test(tc, test_s21_sub_positive_numbers);
  tcase_add_test(tc, test_s21_sub_negative_numbers);
  tcase_add_test(tc, test_s21_sub_mixed_signs);
  tcase_add_test(tc, test_s21_sub_with_scale);
  tcase_add_test(tc, test_s21_sub_zero);
  tcase_add_test(tc, test_21_sub_min_max);
  tcase_add_test(tc, test_21_sub_min_min);
  tcase_add_test(tc, test_21_sub_max_max);
  tcase_add_test(tc, test_21_sub_max_min);
  tcase_add_test(tc, test_21_sub_null_pointer);

  tcase_add_test(tc, test_s21_mul_positive_numbers);
  tcase_add_test(tc, test_s21_mul_negative_positive);
  tcase_add_test(tc, test_s21_mul_big_numbers);
  tcase_add_test(tc, test_s21_mul_null_ptr);
  tcase_add_test(tc, test_s21_mul_overflow_recoverable);
  tcase_add_test(tc, test_s21_mul_huge_scale_rounding);
  tcase_add_test(tc, test_s21_mul_large_shift);
  tcase_add_test(tc, test_s21_mul_too_small);

  tcase_add_test(tc, test_s21_div_simple);
  tcase_add_test(tc, test_s21_div_fractional);
  tcase_add_test(tc, test_s21_div_negative);
  tcase_add_test(tc, test_s21_div_by_zero);
  tcase_add_test(tc, test_s21_div_small_result);
  tcase_add_test(tc, test_s21_div_complex);
  tcase_add_test(tc, test_s21_div_mantissa_overflow_break);
  tcase_add_test(tc, test_s21_div_null_ptr);
  // tcase_add_test(tc, );
  // tcase_add_test(tc, );
  return tc;
}

// TCase *create_comparisons_tcase(void) {
//   TCase *tc = tcase_create("...");
//   tcase_add_test(tc, ...);
//   return tc;
// }

int uint_array_eq(unsigned int *actual, unsigned int *expected, int n) {
  int flag = 0;
  for (int i = 0; !flag && i < n; ++i) {
    flag = !(actual[i] == expected[i]);
  }
  return flag;
}

// from_int_to_decimal
START_TEST(test_s21_decimal_converters_int_to_decimal_normal) {
  int input_int = 1234;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {1234, 0, 0, 0};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

START_TEST(test_s21_decimal_converters_int_to_decimal_zero) {
  int input_int = 0;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {0, 0, 0, 0};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

START_TEST(test_s21_decimal_converters_int_to_decimal_one) {
  int input_int = 1;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {1, 0, 0, 0};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

START_TEST(test_s21_decimal_converters_int_to_decimal_minus_one) {
  int input_int = -1;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {1, 0, 0, 1u << 31};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

START_TEST(test_s21_decimal_converters_int_to_decimal_int_max) {
  int input_int = INT_MAX;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {INT_MAX, 0, 0, 0};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

START_TEST(test_s21_decimal_converters_int_to_decimal_int_min) {
  int input_int = INT_MIN;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {(unsigned int)(-(long long)INT_MIN), 0, 0,
                                  1u << 31};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

START_TEST(test_s21_decimal_converters_int_to_decimal_large_positive) {
  int input_int = 987654321;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {987654321, 0, 0, 0};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

START_TEST(test_s21_decimal_converters_int_to_decimal_large_negative) {
  int input_int = -987654321;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {987654321, 0, 0, 1u << 31};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

START_TEST(test_s21_decimal_converters_int_to_decimal_small_positive) {
  int input_int = 5;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {5, 0, 0, 0};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

START_TEST(test_s21_decimal_converters_int_to_decimal_small_negative) {
  int input_int = -5;
  s21_decimal my_dec;
  unsigned int expected_dec[4] = {5, 0, 0, 1u << 31};

  int result = s21_from_int_to_decimal(input_int, &my_dec);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_dec.bits, expected_dec, 4));
}
END_TEST

// from_decimal_to_int

START_TEST(test_s21_decimal_converters_decimal_to_int_normal) {
  s21_decimal input_dec = {.bits = {1234, 0, 0, 0}};
  int expected_int = 1234;
  int my_int;

  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(expected_int, my_int);
}
END_TEST

// 1. decimal с дробной частью scale = 1
START_TEST(test_s21_decimal_converters_decimal_to_int_scale_nonzero) {
  s21_decimal input_dec = {.bits = {1234, 0, 0, 1 << 16}};  // scale = 1
  int expected_int = 1234 / 10;
  int my_int = 0;

  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(expected_int, my_int);
}
END_TEST

// 2. decimal с bits[1] != 0 (должна быть ошибка)
START_TEST(test_s21_decimal_converters_decimal_to_int_bits1_nonzero) {
  s21_decimal input_dec = {.bits = {123, 1, 0, 0}};
  int my_int = 0;
  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(1, result);
}
END_TEST

// 3. decimal с bits[2] != 0 (должна быть ошибка)
START_TEST(test_s21_decimal_converters_decimal_to_int_bits2_nonzero) {
  s21_decimal input_dec = {.bits = {123, 0, 1, 0}};
  int my_int = 0;
  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(1, result);
}
END_TEST

// 4. decimal с положительным INT_MAX
START_TEST(test_s21_decimal_converters_decimal_to_int_int_max) {
  s21_decimal input_dec = {.bits = {INT_MAX, 0, 0, 0}};
  int expected_int = INT_MAX;
  int my_int = 0;

  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(expected_int, my_int);
}
END_TEST

// 5. decimal с отрицательным INT_MIN
START_TEST(test_s21_decimal_converters_decimal_to_int_int_min) {
  s21_decimal input_dec = {
      .bits = {(unsigned int)(-(long long)INT_MIN), 0, 0, 1u << 31}};
  int expected_int = INT_MIN;
  int my_int = 0;

  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(expected_int, my_int);
}
END_TEST

// 6. decimal с переполнением положительное
START_TEST(test_s21_decimal_converters_decimal_to_int_overflow_positive) {
  s21_decimal input_dec = {.bits = {(unsigned int)INT_MAX + 1u, 0, 0, 0}};
  int my_int = 0;

  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(1, result);
}
END_TEST

// 7. decimal с переполнением отрицательное
START_TEST(test_s21_decimal_converters_decimal_to_int_overflow_negative) {
  s21_decimal input_dec = {
      .bits = {(unsigned int)(-(long long)INT_MIN) + 1u, 0, 0, 1u << 31}};
  int my_int = 0;

  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(1, result);
}
END_TEST

// 8. decimal с дробной частью и отрицательное число
START_TEST(test_s21_decimal_converters_decimal_to_int_scale_negative) {
  s21_decimal input_dec = {
      .bits = {567, 0, 0, (1 << 16) | (1u << 31)}};  // scale = 1, знак = минус
  int expected_int = -(567 / 10);
  int my_int = 0;

  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(expected_int, my_int);
}
END_TEST

// 9. decimal с нулем и scale != 0
START_TEST(test_s21_decimal_converters_decimal_to_int_zero_scale) {
  s21_decimal input_dec = {.bits = {0, 0, 0, 1 << 16}};  // scale = 1
  int expected_int = 0;
  int my_int = 0;

  int result = s21_from_decimal_to_int(input_dec, &my_int);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(expected_int, my_int);
}
END_TEST

START_TEST(test_s21_decimal_converters_decimal_to_int_case12) {
  s21_decimal input_dec = {.bits = {
                               0xFFFFFFFF,  // bits[0] — младшая часть мантиссы
                               0xFFFFFFFF,  // bits[1] — средняя часть мантиссы
                               0xFFFFFFFF,  // bits[2] — старшая часть мантиссы
                               0x801C0000  // bits[3] — знак + scale
                           }};


  int expected_int = -7;
  int my_int;

  int result = s21_from_decimal_to_int(input_dec, &my_int);

  ck_assert_int_eq(0, result);  // функция должна вернуть 0
  ck_assert_int_eq(expected_int, my_int);  // dst = -7
}
END_TEST

// from_float_to_decimal

START_TEST(test_s21_decimal_converters_from_float_to_decimal) {
  float input_float = 12.375f;
  unsigned int expected_decimal[4] = {12375, 0, 0, 3 << 16};
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_decimal.bits, expected_decimal, 4));
}
END_TEST

// 1. Преобразование нуля
START_TEST(test_s21_decimal_converters_from_float_to_decimal_zero) {
  float input_float = 0.0f;
  unsigned int expected_decimal[4] = {0, 0, 0, 0};
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_decimal.bits, expected_decimal, 4));
}
END_TEST

// 2. Отрицательное число с дробной частью
START_TEST(test_s21_decimal_converters_from_float_to_decimal_negative) {
  float input_float = -45.625f;
  unsigned int expected_decimal[4] = {45625, 0, 0, (3 << 16) | (1u << 31)};
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_decimal.bits, expected_decimal, 4));
}
END_TEST

// 3. Малое положительное число > 1e-28
START_TEST(test_s21_decimal_converters_from_float_to_decimal_small_positive) {
  float input_float = 1.23e-7f;
  unsigned int expected_decimal[4] = {
      123, 0, 0, 9 << 16};  // scale = 9 (1.23e-7 * 10^9 = 123)
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(0, result);

  ck_assert_int_eq(0, uint_array_eq(my_decimal.bits, expected_decimal, 4));
}
END_TEST

// 4. Число меньше минимального (должно вернуть ошибку)
START_TEST(test_s21_decimal_converters_from_float_to_decimal_too_small) {
  float input_float = 1e-30f;
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(1, result);
}
END_TEST

// 5. Очень большое число (должно вернуть ошибку)
START_TEST(test_s21_decimal_converters_from_float_to_decimal_too_large) {
  float input_float = FLT_MAX * 2.0f;
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(1, result);
}
END_TEST

// 6. Положительное число с максимальной точностью float
START_TEST(test_s21_decimal_converters_from_float_to_decimal_precision) {
  float input_float = 12345.6789f;
  unsigned int expected_decimal[4] = {1234568, 0, 0, 2 << 16};
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(0, result);

  ck_assert_int_eq(0, uint_array_eq(my_decimal.bits, expected_decimal, 4));
}
END_TEST

// 7. Отрицательное число с минимальной дробной частью
START_TEST(test_s21_decimal_converters_from_float_to_decimal_negative_small) {
  float input_float = -0.0001234f;
  unsigned int expected_decimal[4] = {
      1234, 0, 0, 7 << 16 | (1u << 31)};  // scale = 7, -0.0001234*10^7=1234
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(0, result);

  ck_assert_int_eq(0, uint_array_eq(my_decimal.bits, expected_decimal, 4));
}
END_TEST

// 8. Положительное число, дробная часть 0
START_TEST(test_s21_decimal_converters_from_float_to_decimal_integer_float) {
  float input_float = 5000.0f;
  unsigned int expected_decimal[4] = {5000, 0, 0, 0};
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_decimal.bits, expected_decimal, 4));
}
END_TEST

// 9. Положительное число с большой дробной частью
START_TEST(test_s21_decimal_converters_from_float_to_decimal_fraction_large) {
  float input_float = 0.9876543f;
  unsigned int expected_decimal[4] = {
      9876543, 0, 0, 7 << 16};  // scale = 7, 0.9876543*10^7=9876543
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(input_float, &my_decimal);
  ck_assert_int_eq(0, result);
ck_assert_int_eq(0, uint_array_eq(my_decimal.bits, expected_decimal, 4));
}
END_TEST

// 10. Проверка конвертации float → decimal для значения 7.922816
START_TEST(test_s21_from_float_to_decimal_specific_7_922816) {
  float src = 7.922816f;
  unsigned int expected_decimal[4] = {7922816, 0, 0, 6 << 16};
  s21_decimal my_decimal;

  int result = s21_from_float_to_decimal(src, &my_decimal);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(0, uint_array_eq(my_decimal.bits, expected_decimal, 4));
}
END_TEST

// from_decimal_to_float
START_TEST(test_s21_decimal_converters_from_decimal_to_float_normal) {
  s21_decimal input_dec = {.bits = {1234375, 0, 0, 3 << 16}};
  float expected_float = 1234.375;
  float my_float;

  int result = s21_from_decimal_to_float(input_dec, &my_float);
  ck_assert_int_eq(0, result);
  ck_assert_double_eq(expected_float, my_float);
}
END_TEST

// 1. Ноль
START_TEST(test_s21_decimal_from_decimal_to_float_zero) {
  s21_decimal input = {.bits = {0, 0, 0, 0}};
  float expected = 0.0f;
  float result;
  ck_assert_int_eq(0, s21_from_decimal_to_float(input, &result));
  ck_assert_float_eq_tol(expected, result, 1e-6);
}
END_TEST

// 2. Положительное целое
START_TEST(test_s21_decimal_from_decimal_to_float_positive_int) {
  s21_decimal input = {.bits = {12345, 0, 0, 0}};  // scale = 0
  float expected = 12345.0f;
  float result;
  ck_assert_int_eq(0, s21_from_decimal_to_float(input, &result));
  ck_assert_float_eq_tol(expected, result, 1e-6);
}
END_TEST

// 3. Положительное с дробной частью
START_TEST(test_s21_decimal_from_decimal_to_float_positive_fraction) {
  s21_decimal input = {.bits = {123456, 0, 0, 3 << 16}};  // scale = 3
  float expected = 123.456f;
  float result;
  ck_assert_int_eq(0, s21_from_decimal_to_float(input, &result));
  ck_assert_float_eq_tol(expected, result, 1e-6);
}
END_TEST

// 4. Отрицательное целое
START_TEST(test_s21_decimal_from_decimal_to_float_negative_int) {
  s21_decimal input = {.bits = {9876, 0, 0, 1u << 31}};  // знак минус, scale=0
  float expected = -9876.0f;
  float result;
  ck_assert_int_eq(0, s21_from_decimal_to_float(input, &result));
  ck_assert_float_eq_tol(expected, result, 1e-6);
}
END_TEST

// 5. Отрицательное с дробной частью
START_TEST(test_s21_decimal_from_decimal_to_float_negative_fraction) {
  s21_decimal input = {
      .bits = {1234567, 0, 0, (4 << 16) | (1u << 31)}};  // scale=4, знак минус
  float expected = -123.4567f;
  float result;
  ck_assert_int_eq(0, s21_from_decimal_to_float(input, &result));
  ck_assert_float_eq_tol(expected, result, 1e-6);
}
END_TEST

// 6. Максимальное значение decimal
START_TEST(test_s21_decimal_from_decimal_to_float_max) {
  s21_decimal input = {
      .bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // scale = 0
  float expected = 79228162514264337593543950335.0f;  // приблизительно
  float result;
  ck_assert_int_eq(0, s21_from_decimal_to_float(input, &result));
  // используем относительную точность
  ck_assert_float_eq_tol(expected, result, 1e20);
}
END_TEST

// 7. Минимальное отрицательное значение decimal
START_TEST(test_s21_decimal_from_decimal_to_float_min_negative) {
  s21_decimal input = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                                1u << 31}};  // знак минус, scale=0
  float expected = -79228162514264337593543950335.0f;
  float result;
  ck_assert_int_eq(0, s21_from_decimal_to_float(input, &result));
  ck_assert_float_eq_tol(expected, result, 1e20);
}
END_TEST

// 8. Decimal с максимальным scale
START_TEST(test_s21_decimal_from_decimal_to_float_max_scale) {
  s21_decimal input = {.bits = {1, 0, 0, 28 << 16}};  // scale = 28
  float expected = 1e-28f;
  float result;
  ck_assert_int_eq(0, s21_from_decimal_to_float(input, &result));
  ck_assert_float_eq_tol(expected, result, 1e-34);
}
END_TEST

// 9. Decimal единица с scale 28
START_TEST(test_s21_decimal_from_decimal_to_float_one_scale_28) {
  s21_decimal input = {
      .bits = {1000000000, 0, 0, 9 << 16}};  // scale = 9 → 1e-9 * 1e9 = 1
  float expected = 1.0f;
  float result;
  ck_assert_int_eq(0, s21_from_decimal_to_float(input, &result));
  ck_assert_float_eq_tol(expected, result, 1e-9);
}
END_TEST

TCase *create_converters_tcase(void) {
  TCase *tc = tcase_create("converters");
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_normal);
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_zero);
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_one);
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_minus_one);
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_int_max);
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_int_min);
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_large_positive);
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_large_negative);
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_small_positive);
  tcase_add_test(tc, test_s21_decimal_converters_int_to_decimal_small_negative);
  tcase_add_test(tc, test_s21_decimal_converters_decimal_to_int_normal);
  tcase_add_test(tc, test_s21_decimal_converters_decimal_to_int_scale_nonzero);
  tcase_add_test(tc, test_s21_decimal_converters_decimal_to_int_bits1_nonzero);
  tcase_add_test(tc, test_s21_decimal_converters_decimal_to_int_bits2_nonzero);
  tcase_add_test(tc, test_s21_decimal_converters_decimal_to_int_int_max);
  tcase_add_test(tc, test_s21_decimal_converters_decimal_to_int_int_min);
  tcase_add_test(tc,
                 test_s21_decimal_converters_decimal_to_int_overflow_positive);
  tcase_add_test(tc,
                 test_s21_decimal_converters_decimal_to_int_overflow_negative);
  tcase_add_test(tc, test_s21_decimal_converters_decimal_to_int_scale_negative);
  tcase_add_test(tc, test_s21_decimal_converters_decimal_to_int_zero_scale);
  tcase_add_test(tc, test_s21_decimal_converters_decimal_to_int_case12);
  tcase_add_test(tc, test_s21_decimal_converters_from_float_to_decimal);
  tcase_add_test(tc, test_s21_decimal_converters_from_float_to_decimal_zero);
  tcase_add_test(tc,
                 test_s21_decimal_converters_from_float_to_decimal_negative);
  tcase_add_test(
      tc, test_s21_decimal_converters_from_float_to_decimal_small_positive);
  tcase_add_test(tc,
                 test_s21_decimal_converters_from_float_to_decimal_too_small);
  tcase_add_test(tc,
                 test_s21_decimal_converters_from_float_to_decimal_too_large);
  tcase_add_test(tc,
                 test_s21_decimal_converters_from_float_to_decimal_precision);
  tcase_add_test(
      tc, test_s21_decimal_converters_from_float_to_decimal_negative_small);
  tcase_add_test(
      tc, test_s21_decimal_converters_from_float_to_decimal_integer_float);
  tcase_add_test(
      tc, test_s21_decimal_converters_from_float_to_decimal_fraction_large);
  tcase_add_test(tc,
                 test_s21_from_float_to_decimal_specific_7_922816);
  tcase_add_test(tc, test_s21_decimal_converters_from_decimal_to_float_normal);
  tcase_add_test(tc, test_s21_decimal_from_decimal_to_float_zero);
  tcase_add_test(tc, test_s21_decimal_from_decimal_to_float_positive_int);
  tcase_add_test(tc, test_s21_decimal_from_decimal_to_float_positive_fraction);
  tcase_add_test(tc, test_s21_decimal_from_decimal_to_float_negative_int);
  tcase_add_test(tc, test_s21_decimal_from_decimal_to_float_negative_fraction);
  tcase_add_test(tc, test_s21_decimal_from_decimal_to_float_max);
  tcase_add_test(tc, test_s21_decimal_from_decimal_to_float_min_negative);
  tcase_add_test(tc, test_s21_decimal_from_decimal_to_float_max_scale);
  tcase_add_test(tc, test_s21_decimal_from_decimal_to_float_one_scale_28);
  return tc;
}

START_TEST(test_s21_floor_positive_with_fraction) {
  s21_decimal value = {{58, 0, 0, 0x00010000}};
  s21_decimal result;

  int status = s21_floor(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_negative_with_fraction) {
  s21_decimal value = {{58, 0, 0, 0x80010000}};
  s21_decimal result;

  int status = s21_floor(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 6);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_s21_floor_positive_integer) {
  s21_decimal value = {{10, 0, 0, 0}};
  s21_decimal result;

  int status = s21_floor(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 10);
}
END_TEST

START_TEST(test_s21_floor_negative_integer) {
  s21_decimal value = {{10, 0, 0, 0x80000000}};
  s21_decimal result;

  int status = s21_floor(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_s21_floor_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal result;

  int status = s21_floor(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_floor_small_negative) {
  s21_decimal value = {{1, 0, 0, 0x80010000}};
  s21_decimal result;

  int status = s21_floor(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq((result.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_s21_floor_small_positive) {
  s21_decimal value = {{1, 0, 0, 0x00010000}};
  s21_decimal result;

  int status = s21_floor(value, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_null_pointer) {
  s21_decimal val;
  s21_from_int_to_decimal(10, &val);

  int status = s21_floor(val, NULL);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_round_normal_positive) {
  s21_decimal val = {{34, 0, 0, 0x00010000}};
  s21_decimal res;

  int status = s21_round(val, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 3);
}
END_TEST

START_TEST(test_s21_round_normal_positive_up) {
  s21_decimal val = {{36, 0, 0, 0x00010000}};
  s21_decimal res;

  int status = s21_round(val, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 4);
}
END_TEST

START_TEST(test_s21_round_half_positive) {
  s21_decimal val = {{35, 0, 0, 0x00010000}};
  s21_decimal res;

  int status = s21_round(val, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 4);
}
END_TEST

START_TEST(test_s21_round_normal_negative) {
  s21_decimal val = {{34, 0, 0, 0x80010000}};
  s21_decimal res;

  int status = s21_round(val, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 3);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_s21_round_normal_negative_up) {
  s21_decimal val = {{36, 0, 0, 0x80010000}};
  s21_decimal res;

  int status = s21_round(val, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 4);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_s21_round_half_negative) {
  s21_decimal val = {{35, 0, 0, 0x80010000}};
  s21_decimal res;

  int status = s21_round(val, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 4);
  ck_assert_int_eq((res.bits[3] >> 31) & 1, 1);
}
END_TEST

START_TEST(test_s21_round_zero) {
  s21_decimal val = {{0, 0, 0, 0}};
  s21_decimal res;

  int status = s21_round(val, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(test_s21_round_small_fraction) {
  s21_decimal val = {{1, 0, 0, 0x00040000}};
  s21_decimal res;

  int status = s21_round(val, &res);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(res.bits[0], 0);
}
END_TEST

START_TEST(test_s21_round_null_pointer) {
  s21_decimal val;
  s21_from_int_to_decimal(10, &val);

  int status = s21_round(val, NULL);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_truncate_simple) {
  s21_decimal val, result;
  // 10.5 -> 10
  s21_from_int_to_decimal(105, &val);
  set_scale(&val, 1);

  int status = s21_truncate(val, &result);

  ck_assert_int_eq(status, S21_OK);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_s21_truncate_negative) {
  s21_decimal val, result;
  s21_from_int_to_decimal(-105, &val);
  set_scale(&val, 1);

  int status = s21_truncate(val, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_s21_truncate_large_scale) {
  s21_decimal val, result;
  // 123.456 -> 123
  s21_from_int_to_decimal(123456, &val);
  set_scale(&val, 3);

  int status = s21_truncate(val, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_s21_truncate_no_fraction) {
  s21_decimal val, result;
  s21_from_int_to_decimal(10, &val);

  int status = s21_truncate(val, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_s21_truncate_null_pointer) {
  s21_decimal val;
  s21_from_int_to_decimal(10, &val);

  int status = s21_truncate(val, NULL);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_s21_negate_positive) {
  s21_decimal val, result;
  s21_from_int_to_decimal(10, &val);

  int status = s21_negate(val, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_s21_negate_null_pointer) {
  s21_decimal val;
  s21_from_int_to_decimal(10, &val);

  int status = s21_negate(val, NULL);

  ck_assert_int_eq(status, 1);
}
END_TEST

TCase *create_other_funcs_tcase(void) {
  TCase *tc = tcase_create("other");
  tcase_add_test(tc, test_s21_floor_positive_with_fraction);
  tcase_add_test(tc, test_s21_floor_negative_with_fraction);
  tcase_add_test(tc, test_s21_floor_positive_integer);
  tcase_add_test(tc, test_s21_floor_negative_integer);
  tcase_add_test(tc, test_s21_floor_zero);
  tcase_add_test(tc, test_s21_floor_small_negative);
  tcase_add_test(tc, test_s21_floor_small_positive);
  tcase_add_test(tc, test_s21_floor_null_pointer);

  tcase_add_test(tc, test_s21_round_normal_positive);
  tcase_add_test(tc, test_s21_round_normal_positive_up);
  tcase_add_test(tc, test_s21_round_half_positive);
  tcase_add_test(tc, test_s21_round_normal_negative);
  tcase_add_test(tc, test_s21_round_normal_negative_up);
  tcase_add_test(tc, test_s21_round_half_negative);
  tcase_add_test(tc, test_s21_round_zero);
  tcase_add_test(tc, test_s21_round_small_fraction);
  tcase_add_test(tc, test_s21_round_null_pointer);

  tcase_add_test(tc, test_s21_truncate_simple);
  tcase_add_test(tc, test_s21_truncate_negative);
  tcase_add_test(tc, test_s21_truncate_large_scale);
  tcase_add_test(tc, test_s21_truncate_no_fraction);
  tcase_add_test(tc, test_s21_truncate_null_pointer);

  tcase_add_test(tc, test_s21_negate_positive);
  tcase_add_test(tc, test_s21_negate_null_pointer);
  return tc;
}

Suite *s21_decimal_suite(void) {
  Suite *s = suite_create("s21_decimal");

  suite_add_tcase(s, create_arithmetic_tcase());
  //   suite_add_tcase(s, create_comparison_tcase());
  suite_add_tcase(s, create_converters_tcase());
  suite_add_tcase(s, create_other_funcs_tcase());

  return s;
}

int main(void) {
  int number_failed = 0;
  Suite *s;
  SRunner *sr;

  s = s21_decimal_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
