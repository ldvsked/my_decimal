#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return S21_DEREFERENCING_NULL_POINTER_ATTEMPT;

  init_decimal(result);
  int sign1 = get_sign(value_1);
  int sign2 = get_sign(value_2);
  int result_sign = sign1 ^ sign2;

  int scale1 = get_scale(value_1);
  int scale2 = get_scale(value_2);
  int result_scale = scale1 + scale2;

  s21_decimal temp_result;
  init_decimal(&temp_result);

  return_code rc = S21_OK;
  int overflow = 0;

  for (int i = 0; i < 96; i++) {
    if (get_bit(value_2, i)) {
      int carry = add_bits(&temp_result, temp_result, value_1);
      if (carry) {
        overflow = 1;
      }
    }
    if (shift_left(&value_1)) {
      // переполнение случается только в том случае, если у нас дальше есть
      // значащие биты пример: пусть вместимость - 4 бита 1000
      //   x
      // 0001
      // первая итерация - окей (0 + 1000)
      // вторая итерация - это уже могло бы быть 10000 - выходит за пределы 4
      // битов, НО дальше одни нули (результат для второй итерации в итоге будет
      // ТИПА 1000 + 0 * 10000 - на самом деле конечно нет, потому что 10000 не
      // помещается, нет такого числа просто) значит переполнения быть не может

      // а вот если бы было
      // 1000
      //   x
      // 0011
      // это бы уже не прокнуло
      int has_more_bits = 0;
      for (int k = i + 1; k < 96; k++) {
        if (get_bit(value_2, k)) has_more_bits = 1;
      }

      if (has_more_bits) overflow = 1;
    }
  }

  if (result_scale > 28) {
    rc = S21_TOO_LARGE;
  }

  if (rc == S21_OK && overflow) {
    rc = result_sign ? S21_TOO_SMALL : S21_TOO_LARGE;
  }

  *result = temp_result;
  set_scale(result, result_scale);
  set_sign(result, result_sign);

  return rc;
}
