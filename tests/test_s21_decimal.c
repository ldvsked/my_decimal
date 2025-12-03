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
  ck_assert_int_eq(get_scale(result), 0);
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

START_TEST(test_s21_sub_positive_numbers) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(100, &val1);
  s21_from_int_to_decimal(50, &val2);

  int status = s21_sub(val1, val2, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 150);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_s21_sub_negative_numbers) {
  s21_decimal val1, val2, result;
  s21_from_int_to_decimal(-100, &val1);
  s21_from_int_to_decimal(-50, &val2);
  s21_decimal result;

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
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(get_scale(result), 0);
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

  int status = s21_sub(max_dec, min_dec, &result);

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

  tcase_ass_test(tc, test_s21_sub_positive_numbers);
  tcase_add_test(tc, test_s21_sub_negative_numbers);
  tcase_add_test(tc, test_s21_sub_mixed_signs);
  tcase_add_test(tc, test_s21_sub_with_scale);
  tcase_add_test(tc, test_s21_sub_zero);
  tcase_add_test(tc, test_21_sub_min_max);
  tcase_add_test(tc, test_21_sub_min_min);
  tcase_add_test(tc, test_21_sub_max_max);
  tcase_add_test(tc, test_21_sub_max_min);

  // tcase_add_test(tc, );
  // tcase_add_test(tc, );
  // tcase_add_test(tc, );
  // tcase_add_test(tc, );
  return tc;
}

// TCase *create_comparisons_tcase(void) {
//   TCase *tc = tcase_create("...");
//   tcase_add_test(tc, ...);
//   return tc;
// }

// TCase *create_..._tcase(void) {
//   TCase *tc = tcase_create("...");
//   tcase_add_test(tc, ...);
//   return tc;
// }

// TCase *create_other_funcs_tcase(void) {
//   TCase *tc = tcase_create("...");
//   tcase_add_test(tc, ...);
//   return tc;
// }

Suite *s21_decimal_suite(void) {
  Suite *s = suite_create("s21_decimal");

  suite_add_tcase(s, create_arithmetic_tcase());
  //   suite_add_tcase(s, create_comparison_tcase());
  //   suite_add_tcase(s, create_convertors_tcase());
  //   suite_add_tcase(s, create_other_funcs_tcase());

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
