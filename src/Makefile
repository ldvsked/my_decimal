CC = gcc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: s21_decimal.a
	$(CC) $(CFLAGS) main.c s21_decimal.a -o test -lm

s21_decimal.a: s21_decimal.o \
               s21_is_equal.o \
               s21_is_greater_or_equal.o \
               s21_is_less_or_equal.o \
               s21_is_less.o \
               help_func.o\
               s21_is_not_equal.o \
               s21_is_greater.o
	ar rcs s21_decimal.a $^

test: all
	./test

rebuild: clean all

clean:
	rm -f test *.o *.a