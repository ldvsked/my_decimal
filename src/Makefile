CC = gcc 
CFLAGS = -Wall -Wextra -Werror
GCOV_FLAGS = --coverage
LDFLAGS = -lcheck -lm -lpthread -lsubunit -lrt
SRCS = $(wildcard *.c)
LIB_SRCS = $(filter-out main.c, $(wildcard *.c))
OBJS = $(SRCS:.c=.o)
GCOV_OBJS = $(SRCS:.c=_gcov.o)
TEST_DIR = ../tests
REPORT_DIR = report

all: s21_decimal.a

test:
	cd $(TEST_DIR) && $(MAKE) test

# test: all
# 	./test

s21_decimal.a: $(OBJS)
	ar rcs $@ $^
	ranlib $@

%.o: %.c s21_decimal.h
	$(CC) -c $(CFLAGS) $< -o $@

%_gcov.o: %.c s21_decimal.h
	$(CC) -c $(CFLAGS) $(GCOV_FLAGS) $< -o $@

s21_decimal_gcov.a: $(GCOV_OBJS)
	ar rcs $@ $^
	ranlib $@


gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(LIB_SRCS)
	ar rcs s21_decimal.a *.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_DIR)/*.c s21_decimal.a -o gcov_test $(LDFLAGS)
	./gcov_test
	gcovr -r . --html --html-details -o coverage.html
	@echo "Report was created: coverage.html"

rebuild: clean all

clean:
	rm -rf test *.o *.a *.gcno *.gcda *.css *.html ../tests/test_s21_decimal 

lint:
	clang-format -i *.c *.h ../tests/*.c

.PHONY: test gcov_report clean lint
