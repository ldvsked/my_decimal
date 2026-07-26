#include "my_decimal.h"

int my_from_decimal_to_int(my_decimal src, int *dst) {
  int flag = 0;
  int pow_10 =
      (src.bits[3] << 1) >>
      17;  // ну по идее убрали на всякий случай знаковый бит и сдвинули обратно
  if ((src.bits[1] != 0 || src.bits[2] != 0) &&
      !pow_10) {  // не влезает и делиться потом не будет
    flag = 1;
  }

  long long ABS_MAX = pow(2, 31) - 1;

  unsigned int b0 = src.bits[0];
  unsigned int b1 = src.bits[1];
  unsigned int b2 = src.bits[2];

  for (int i = 0; i < pow_10; ++i) {
    long long carry;

    // старший разряд
    carry = b2 % 10;
    b2 /= 10;

    // средний разряд
    long long temp = (carry << 32) | b1;
    b1 = temp / 10;
    carry = temp % 10;

    // младший разряд
    temp = (carry << 32) | b0;
    b0 = temp / 10;
    carry = temp % 10;
  }

  // long long abs = src.bits[0] / pow(10, pow_10);
  int sign = pow(-1, (src.bits[3] >> 31) & 1);

  if (b1 || b2 || b0 > ABS_MAX + 1 || (b0 == ABS_MAX + 1 && sign != (-1))) {
    flag = 1;
  } else {
    *dst = sign * (int)b0;
  }
  return flag;
}