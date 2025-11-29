#include<stdio.h>
#include"s21_decimal.h"

void print_binary(unsigned int num) {
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

int main(){

    int test;
    scanf("%d", &test);
    s21_decimal number;
    s21_from_int_to_decimal(test, &number);
    print_decimal_binary(number);

    int output_int;
    s21_from_decimal_to_int(number, &output_int);
    printf("%d\n", output_int);

    // float input_fl;
    // scanf("%f", &input_fl);
    // s21_decimal number_dec;
    // s21_from_float_to_decimal(input_fl, &number_dec);
    // print_decimal_binary(number_dec);
    // float output_fl;
    // s21_from_decimal_to_float(number_dec, &output_fl);
    // printf("%f\n", output_fl);

    return 0;
}