CC = gcc 
CFLAGS = -Wall -Wextra -Werror -std=c11
CHECK_LIBS = -lcheck -lsubunit -pthread -lm
ADD = `pkg-config --cflags --libs check`
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

all: s21_decimal.a
	$(CC) $(CFLAGS) ../test/converters_test.c s21_decimal.a -o test $(CHECK_LIBS)
	
test: clean all
	./test

s21.o:
	$(CC) $(CFLAGS) -c s21*.c

s21_decimal.a: s21_from_decimal_to_int.o \
s21_from_decimal_to_float.o \
s21_from_int_to_decimal.o \
s21_from_float_to_decimal.o
	ar rcs s21_decimal.a  $^

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c s21*.c
	ar rcs s21_decimal.a s21_from_decimal_to_int.o s21_from_decimal_to_float.o s21_from_int_to_decimal.o s21_from_float_to_decimal.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ../test/converters_test.c s21_decimal.a -o test $(ADD)
	./test
	gcovr -r . --html --html-details -o coverage.html

rebuild: clean all

clean:
	rm -rf test *.o *.a test *.css *.html *.gc*