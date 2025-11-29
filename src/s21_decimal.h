#ifndef s21_decimal_h
#define s21_decimal_h

typedef struct 
{
    unsigned int bits[4];
} s21_decimal;

int get_sign(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
void normalize_scale(s21_decimal *value_1, s21_decimal *value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif  // s21_decimal_h
