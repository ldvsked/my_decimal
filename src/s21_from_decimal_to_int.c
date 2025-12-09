#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 0;
  if (src.bits[1] != 0 || src.bits[2] != 0) {
    flag = 1;
  }

  long long ABS_MAX = pow(2, 31) - 1;

  int pow_10 =
      (src.bits[3] << 1) >>
      17;  // ну по идее убрали на всякий случай знаковый бит и сдвинули обратно
  long long abs = src.bits[0] / pow(10, pow_10);
  int sign = pow(-1, (src.bits[3] >> 31) & 1);

  if (abs > ABS_MAX + 1 || (abs == ABS_MAX + 1 && sign != (-1))) {
    flag = 1;
  } else {
    *dst = sign * (int)abs;
  }
  return flag;
}