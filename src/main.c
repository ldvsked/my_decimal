#include <stdio.h>

#include "s21_decimal.h"
#include "comparison_operators.h"

int main(){
    
    s21_decimal num = {{200,1000,124321432,0}};
    print_decimal_binary(num);
    unsigned int bits[3]= {num.bits[0],num.bits[1],num.bits[2]};
    unsigned long res = divide_by_10(bits);
    print_binary(res);
}