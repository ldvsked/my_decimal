CC = gcc 
CFLAGS = -Wall -Wextra -Werror
GCOV_FLAGS = --coverage
LDFLAGS = -lcheck -lm -lpthread -lsubunit -lrt
SRCS = $(wildcard *.c)
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

gcov_report: clean s21_decimal_gcov.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRCS) $(TEST_DIR)/*.c $(LDFLAGS) -o gcov_test ./gcov_test
	genhtml -o $(REPORT_DIR) coverage.info
	open $(REPORT_DIR)/index.html

rebuild: clean all

clean:
	rm -rf test *.o *.a

lint:
	clang-format -i *.c *.h ../tests/*.c

.PHONY: test gcov_report clean lint
