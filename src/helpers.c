#include "s21_decimal.h"

int get_sign(s21_decimal value) {
    return (value.bits[3] >> 31) & 1;
}

void set_sign(s21_decimal *value, int sign) {
    if (sign) {
        value->bits[3] |= (1 << 31);
    } else {
        value->bits[3] &= ~(1 << 31);
    }
}

int get_scale(s21_decimal value) {
    return (value.bits[3] >> 16) & 0xFF;
}

void set_scale(s21_decimal *value, int scale) {
    value->bits[3] &= 0x80000000;
    value->bits[3] |= (scale << 16);
}