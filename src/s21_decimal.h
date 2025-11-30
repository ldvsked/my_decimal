#ifndef s21_decimal_h
#define s21_decimal_h

typedef struct {
  unsigned int bits[4];
} s21_decimal;

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif  // s21_decimal_h
