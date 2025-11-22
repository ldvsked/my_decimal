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
    s21_decimal numder;
    s21_from_int_to_decimal(test, &numder);
    print_decimal_binary(numder);

    return 0;
}