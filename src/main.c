#include <stdio.h>

#include "s21_decimal.h"
#include "comparison_operators.h"

int main(){
    
    s21_decimal num1 = {{200,0,0,0}};
    s21_decimal num2 = {{800,0,0,0}};
    set_degree(&num1,5);
    set_degree(&num2,8);
    s21_is_greater(num1,num2);
}