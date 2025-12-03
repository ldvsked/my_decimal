#ifndef s21_decimal_h
#define s21_decimal_h

#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// helpers
void init_decimal(s21_decimal* value);
void print_decimal(s21_decimal value);
int get_sign(s21_decimal value);
void set_sign(s21_decimal* value, int sign);
int get_scale(s21_decimal value);
void set_scale(s21_decimal* value, int scale);
void normalize_scale(s21_decimal* value_1, s21_decimal* value_2);
int compare_bits(s21_decimal value_1, s21_decimal value_2);
int add_bits(s21_decimal* res, s21_decimal v1, s21_decimal v2);
int sub_bits(s21_decimal* res, s21_decimal v1, s21_decimal v2);
void set_decimal(s21_decimal* dst, int* bits, int scale, int sign);

int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);

#endif  // s21_decimal_h
