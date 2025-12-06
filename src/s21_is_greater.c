#include "comparison_operators.h"

int s21_is_greater(s21_decimal num_1, s21_decimal num_2) {
    int res = 0;
    int sign1 = get_sign(num_1);
    int sign2 = get_sign(num_2);
    unsigned int bits1[3] = {num_1.bits[0], num_1.bits[1], num_1.bits[2]};
    unsigned int bits2[3] = {num_2.bits[0], num_2.bits[1], num_2.bits[2]};

    if (!is_zero(bits1) && !is_zero(bits2)) {
        if (sign1 == sign2) {
            s21_decimal m1, m2;
            if (align_decimal_scales(num_1, num_2, &m1, &m2)) {
                int compared = 0;
                for (int i = 2; i >= 0 && !compared; i--) {
                    if (m1.bits[i] != m2.bits[i]) {
                        res = (m1.bits[i] > m2.bits[i]) ? !sign1 : sign1;
                        compared = 1;
                    }
                }
            }
        } else if (sign1 < sign2) {
            res = 1;
        }
    } else {
        if (!is_zero(bits1) && is_zero(bits2)) {
            res = !sign1;
        } else if (is_zero(bits1) && !is_zero(bits2)) {
            res = sign2;
        }
    }
    return res;
}
