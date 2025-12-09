#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../src/s21_decimal.h"

int uint_array_eq(unsigned int* actual, unsigned int* expected, int n) {
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

// from_float_to_decimal

// 0. Простой тест с положительным числом
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

Suite* test_s21_decimal_converters_suite(void) {
  Suite* s = suite_create("s21_decimal_converters");

  TCase* tc_int_to_dec = tcase_create("from_int_to_decimal");
  tcase_add_test(tc_int_to_dec,
                 test_s21_decimal_converters_int_to_decimal_normal);
  tcase_add_test(tc_int_to_dec,
                 test_s21_decimal_converters_int_to_decimal_zero);
  tcase_add_test(tc_int_to_dec, test_s21_decimal_converters_int_to_decimal_one);
  tcase_add_test(tc_int_to_dec,
                 test_s21_decimal_converters_int_to_decimal_minus_one);
  tcase_add_test(tc_int_to_dec,
                 test_s21_decimal_converters_int_to_decimal_int_max);
  tcase_add_test(tc_int_to_dec,
                 test_s21_decimal_converters_int_to_decimal_int_min);
  tcase_add_test(tc_int_to_dec,
                 test_s21_decimal_converters_int_to_decimal_large_positive);
  tcase_add_test(tc_int_to_dec,
                 test_s21_decimal_converters_int_to_decimal_large_negative);
  tcase_add_test(tc_int_to_dec,
                 test_s21_decimal_converters_int_to_decimal_small_positive);
  tcase_add_test(tc_int_to_dec,
                 test_s21_decimal_converters_int_to_decimal_small_negative);

  TCase* tc_dec_to_int = tcase_create("from_dec_to_int");
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_normal);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_scale_nonzero);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_bits1_nonzero);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_bits2_nonzero);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_int_max);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_int_min);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_overflow_positive);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_overflow_negative);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_scale_negative);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_zero_scale);
  tcase_add_test(tc_dec_to_int,
                 test_s21_decimal_converters_decimal_to_int_case12);

  TCase* tc_float_to_dec = tcase_create("from_float_to_dec");
  tcase_add_test(tc_float_to_dec,
                 test_s21_decimal_converters_from_float_to_decimal);
  tcase_add_test(tc_float_to_dec,
                 test_s21_decimal_converters_from_float_to_decimal_zero);
  tcase_add_test(tc_float_to_dec,
                 test_s21_decimal_converters_from_float_to_decimal_negative);
  tcase_add_test(
      tc_float_to_dec,
      test_s21_decimal_converters_from_float_to_decimal_small_positive);
  tcase_add_test(tc_float_to_dec,
                 test_s21_decimal_converters_from_float_to_decimal_too_small);
  tcase_add_test(tc_float_to_dec,
                 test_s21_decimal_converters_from_float_to_decimal_too_large);
  tcase_add_test(tc_float_to_dec,
                 test_s21_decimal_converters_from_float_to_decimal_precision);
  tcase_add_test(
      tc_float_to_dec,
      test_s21_decimal_converters_from_float_to_decimal_negative_small);
  tcase_add_test(
      tc_float_to_dec,
      test_s21_decimal_converters_from_float_to_decimal_integer_float);
  tcase_add_test(
      tc_float_to_dec,
      test_s21_decimal_converters_from_float_to_decimal_fraction_large);
  tcase_add_test(tc_float_to_dec,
                 test_s21_from_float_to_decimal_specific_7_922816);

  TCase* tc_decimal_to_float = tcase_create("from_decimal_to_float");
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_converters_from_decimal_to_float_normal);
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_from_decimal_to_float_zero);
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_from_decimal_to_float_positive_int);
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_from_decimal_to_float_positive_fraction);
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_from_decimal_to_float_negative_int);
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_from_decimal_to_float_negative_fraction);
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_from_decimal_to_float_max);
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_from_decimal_to_float_min_negative);
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_from_decimal_to_float_max_scale);
  tcase_add_test(tc_decimal_to_float,
                 test_s21_decimal_from_decimal_to_float_one_scale_28);

  suite_add_tcase(s, tc_int_to_dec);
  suite_add_tcase(s, tc_dec_to_int);
  suite_add_tcase(s, tc_float_to_dec);
  suite_add_tcase(s, tc_decimal_to_float);
  suite_add_tcase(s, tc_decimal_to_float);
  return s;
}

int main() {
  Suite* s = test_s21_decimal_converters_suite();

  SRunner* runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);

  int failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failed ? 1 : 0;
}
