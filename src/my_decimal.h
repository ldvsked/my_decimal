#ifndef my_decimal_h
#define my_decimal_h

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} my_decimal;

typedef struct {
  unsigned int bits[7];
} my_big_decimal;

typedef enum return_code {
  S21_OK = 0,
  S21_TOO_LARGE = 1,
  S21_TOO_SMALL = 2,
  S21_DIV_BY_ZERO = 3,
  S21_DEREFERENCING_NULL_POINTER_ATTEMPT = 4
} return_code;

// arithmetic operators
int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result);

// helpers
void init_decimal(my_decimal *value);
void set_decimal(my_decimal *dst, unsigned int b0, unsigned int b1,
                 unsigned int b2, int scale, int sign);
int get_sign(my_decimal value);
void set_sign(my_decimal *value, int sign);
int get_scale(my_decimal value);
void set_scale(my_decimal *value, int scale);
void normalize_scale(my_decimal *value_1, my_decimal *value_2);
my_big_decimal decimal_to_big(my_decimal value);
void big_to_decimal(my_big_decimal src, my_decimal *dst);
int compare_bits(my_decimal value_1, my_decimal value_2);
int add_bits(my_decimal *res, my_decimal v1, my_decimal v2);
int sub_bits(my_decimal *res, my_decimal v1, my_decimal v2);

void add_big(my_big_decimal value_1, my_big_decimal value_2,
             my_big_decimal *result);
void shift_left_big(my_big_decimal *dst, int shift);
my_big_decimal mul_mantissa(my_decimal value_1, my_decimal value_2);
int div_by_10_big(my_big_decimal *value);
int is_overflow_big(my_big_decimal value);
void add_one_big(my_big_decimal *value);
void bank_rounding(my_big_decimal *value, int remainder);

int get_bit(my_decimal value, int index);
int shift_left(my_decimal *value);
int is_full_value_zero(my_decimal value);
void div_integer_mantissa(my_decimal dividend, my_decimal divisor,
                          my_decimal *quotient, my_decimal *remainder);
int mul_by_10(my_decimal *value);

// comparison operators
int my_is_equal(my_decimal num1, my_decimal num2);
int my_is_not_equal(my_decimal num_1, my_decimal num_2);
int my_is_greater_or_equal(my_decimal num_1, my_decimal num_2);
int my_is_less_or_equal(my_decimal num_1, my_decimal num_2);
int my_is_greater(my_decimal num_1, my_decimal num_2);
int my_is_less(my_decimal num_1, my_decimal num_2);

// convertors and parsers
int my_from_int_to_decimal(int src, my_decimal *dst);
int my_from_decimal_to_int(my_decimal src, int *dst);
int my_from_float_to_decimal(float src, my_decimal *dst);
int my_from_decimal_to_float(my_decimal src, float *dst);

// other functions
int my_round(my_decimal value, my_decimal *result);
int my_floor(my_decimal value, my_decimal *result);
int my_truncate(my_decimal value, my_decimal *result);
int my_negate(my_decimal value, my_decimal *result);

// egor's help_func
void set_degree(my_decimal *ch, int exp);
int get_degree(const my_decimal ch);
int is_zero(const unsigned int bits[3]);

my_decimal normalize_decimal(my_decimal num);
int divide_by_10(unsigned int bits[3]);
int multiply_by_10(unsigned int value[3]);
int align_decimal_scales(my_decimal value_1, my_decimal value_2,
                         my_decimal *out_1, my_decimal *out_2);

#endif  // my_decimal_h
