#ifndef s21_decimal_h
#define s21_decimal_h

typedef struct 
{
    unsigned int bits[4];
} s21_decimal;


int s21_from_int_to_decimal(int src, s21_decimal *dst);

#endif  // s21_decimal_h
