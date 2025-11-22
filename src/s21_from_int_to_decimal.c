#include"s21_decimal.h"
#include <stdlib.h>
#include <limits.h>


int s21_from_int_to_decimal(int src, s21_decimal *dst){

    int sign = !(src >= 0); // 1 - если отрицательный
   
    unsigned int src_abs;
    if (src == INT_MIN){
        src_abs = (unsigned int)((-1) * (long long)src);
    }else {
        src_abs = abs(src);
    }
    
    dst->bits[0] = src_abs;
    dst->bits[1] = 0;
    dst->bits[2] = 0;

    if (sign){
        dst->bits[3] = 1u << 31;
    }else {
        dst->bits[3] = 0;
    }
    
    return 0;
}
