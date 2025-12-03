
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lcheck -lm -lpthread -lrt -lsubunit
SRC_DIR = ../src
LIBRARY = $(SRC_DIR)/s21_decimal.a

TEST_SOURCES = test_s21_decimal.c
TEST_EXECUTABLE = test_s21_decimal


test: $(TEST_EXECUTABLE)
	@./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_SOURCES) $(LIBRARY)
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(TEST_SOURCES) $(LIBRARY) $(LDFLAGS) -o $@
