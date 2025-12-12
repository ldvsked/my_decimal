#ifndef s21_decimal_h
#define s21_decimal_h

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[7];
} s21_big_decimal;

typedef enum return_code {
  S21_OK = 0,
  S21_TOO_LARGE = 1,
  S21_TOO_SMALL = 2,
  S21_DIV_BY_ZERO = 3,
  S21_DEREFERENCING_NULL_POINTER_ATTEMPT = 4
} return_code;

// arithmetic operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// helpers
void init_decimal(s21_decimal *value);
void print_decimal(s21_decimal value);
int get_sign(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
void normalize_scale(s21_decimal *value_1, s21_decimal *value_2);
s21_big_decimal decimal_to_big(s21_decimal value);
void big_to_decimal(s21_big_decimal src, s21_decimal *dst);
int add_abs_with_scale(s21_decimal v1, s21_decimal v2, int scale, int sign,
                       s21_decimal *result);
int compare_bits(s21_decimal value_1, s21_decimal value_2);
int add_bits(s21_decimal *res, s21_decimal v1, s21_decimal v2);
int add_bits_temp(s21_decimal *result, s21_decimal one);
int sub_bits(s21_decimal *res, s21_decimal v1, s21_decimal v2);
void set_decimal(s21_decimal *dst, int *bits, int scale, int sign);

int get_bit_big(s21_big_decimal dst, int index);
void add_big(s21_big_decimal value_1, s21_big_decimal value_2,
             s21_big_decimal *result);
void shift_left_big(s21_big_decimal *dst, int shift);
s21_big_decimal mul_mantissa(s21_decimal value_1, s21_decimal value_2);
int div_by_10_big(s21_big_decimal *value);
int is_overflow_big(s21_big_decimal value);
void add_one_big(s21_big_decimal *value);
void bank_rounding(s21_big_decimal *value, int remainder);

int get_bit(s21_decimal value, int index);
int shift_left(s21_decimal *value);
int is_full_value_zero(s21_decimal value);
void div_integer_mantissa(s21_decimal dividend, s21_decimal divisor,
                          s21_decimal *quotient, s21_decimal *remainder);
int mul_by_10(s21_decimal *value);

// comparison operators
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_greater_or_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_less_or_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_greater(s21_decimal num_1, s21_decimal num_2);
int s21_is_less(s21_decimal num_1, s21_decimal num_2);

// convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// other functions
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// egor's help_func
void print_binary(int num);
void print_decimal_binary(s21_decimal number);
void set_degree(s21_decimal *ch, int exp);
void set_sign(s21_decimal *ch, const int sign);
int get_degree(const s21_decimal ch);
int get_sign(const s21_decimal ch);
int is_zero(const unsigned int bits[3]);
void print_decimal_normal(const s21_decimal numb);

s21_decimal normalize_decimal(s21_decimal num);
int divide_by_10(unsigned int bits[3]);
int multiply_by_10(unsigned int value[3]);
int align_decimal_scales(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *out_1, s21_decimal *out_2);

#endif  // s21_decimal_h
