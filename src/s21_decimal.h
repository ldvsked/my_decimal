#ifndef s21_decimal_h
#define s21_decimal_h

#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef enum return_code {
  S21_OK = 0,
  S21_TOO_LARGE = 1,
  S21_TOO_SMALL = 2,
  S21_DIV_BY_ZERO = 3,
  S21_DEREFERENCING_NULL_POINTER_ATTEMPT = 4
} return_code;

// arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// other functions
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// helpers
void init_decimal(s21_decimal *value);
void print_decimal(s21_decimal value);
int get_sign(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
void normalize_scale(s21_decimal *value_1, s21_decimal *value_2);
int compare_bits(s21_decimal value_1, s21_decimal value_2);
int add_bits(s21_decimal *res, s21_decimal v1, s21_decimal v2);
int sub_bits(s21_decimal *res, s21_decimal v1, s21_decimal v2);
void set_decimal(s21_decimal *dst, int *bits, int scale, int sign);

int get_bit(s21_decimal value, int index);
int shift_left(s21_decimal *value);
int is_zero(s21_decimal value);
void div_integer_mantissa(s21_decimal dividend, s21_decimal divisor,
                          s21_decimal *quotient, s21_decimal *remainder);
int mul_by_10(s21_decimal *value);

// convertors
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// comparisons
void print_binary(int num);
void print_decimal_binary(s21_decimal number);
void set_degree(s21_decimal* ch, int exp);
void set_sign(s21_decimal* ch, const int sign);
int get_degree(const s21_decimal ch);
int get_sign(const s21_decimal ch);
int is_zero(const unsigned int bits[3]);
void print_decimal_normal(const s21_decimal numb);


#endif  // s21_decimal_h
