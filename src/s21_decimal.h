#ifndef s21_decimal_h
#define s21_decimal_h

typedef struct 
{
    unsigned int bits[4];
} s21_decimal;

void print_binary(int num);

void print_decimal_binary(s21_decimal number);

void set_degree(s21_decimal* ch, int exp);

void set_sign(s21_decimal* ch, const int sign);

int get_degree(const s21_decimal ch);

int get_sign(const s21_decimal ch);

int is_zero(const unsigned int bits[3]);

void print_decimal_normal(const s21_decimal numb);

#endif
