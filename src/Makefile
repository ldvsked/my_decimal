CC = gcc 
CFLAGS = -Wall -Wextra -Werror

all: s21_decimal.a 
	$(CC) $(CFLAGS) main.c s21_decimal.a -o test -lm

s21.o:
	$(CC) $(CFLAGS) -c s21*.c

s21_decimal.a: s21_from_decimal_to_int.o \
s21_from_decimal_to_float.o \
s21_from_int_to_decimal.o \
s21_from_float_to_decimal.o
	ar rcs s21_decimal.a  $^

test: all
	./test

rebuild: clean all

clean:
	rm -rf test *.o *.a