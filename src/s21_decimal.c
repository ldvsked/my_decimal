#include <stdio.h>
#include <string.h>

#include "s21_decimal.h"

void print_binary(int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 8 == 0) printf("|");
    }
    printf("\n");
}

void print_decimal_binary(s21_decimal number) {
    for (int i = 0; i < 4; i++) {
        printf("%d :", i);
        print_binary(number.bits[i]);
        printf("---------------------------------------\n");
    }
}

void set_degree(s21_decimal* ch, int exp) {
    ch->bits[3] = (ch->bits[3] & 0x8000FFFF) | (exp << 16);
}

void set_sign(s21_decimal* ch, const int sign) {
    if (sign) {
        ch->bits[3] |= (1 << 31);
    } else {
        ch->bits[3] &= ~(1 << 31);
    }
}

int get_degree(const s21_decimal ch) {
    return (ch.bits[3] >> 16) & 255;
}

int get_sign(const s21_decimal ch) {
    return ((ch.bits[3] >> 31) & 1);
}

// Функция для деления 96-битного числа на 10
int divide_by_10(unsigned int bits[3]) {
    unsigned long long remainder = 0;
    for (int i = 2; i >= 0; i--) {
        unsigned long long temp = (remainder << 32) | bits[i];
        bits[i] = temp / 10;
        remainder = temp % 10;
    }
    return (int)remainder;
}

// Проверка, что все три части равны нулю
int is_zero(const unsigned int bits[3]) {
    return bits[0] == 0 && bits[1] == 0 && bits[2] == 0;
}

// Основная функция вывода decimal в десятичном виде
void print_decimal_normal(const s21_decimal numb) {//Вот эту хуйню я не осилил...
    int sign = get_sign(numb);
    int scale = get_degree(numb);
    unsigned int bits[3] = {numb.bits[0], numb.bits[1], numb.bits[2]};
    if (is_zero(bits)) {
        printf("0\n");
        return;
    }
    if (sign) printf("-");
    
    // Преобразуем 96-битное число в строку (в обратном порядке)
    char digits[100] = {0};
    int digit_count = 0;
    
    // Получаем цифры путем деления на 10
    while (!is_zero(bits)) {
        int digit = divide_by_10(bits);
        digits[digit_count++] = '0' + digit;
    }
        
    if (scale == 0) {
        for (int i = digit_count - 1; i >= 0; i--) {
            printf("%c", digits[i]);
        }
    } else {
        if (digit_count <= scale) {
            printf("0.");
            for (int i = 0; i < scale - digit_count; i++) {
                printf("0");
            }
            for (int i = digit_count - 1; i >= 0; i--) {
                printf("%c", digits[i]);
            }
        } else {
            for (int i = digit_count - 1; i >= 0; i--) {
                printf("%c", digits[i]);
                if (i == scale) {
                    printf(".");
                }
            }
        }
    }
    printf("\n");
}