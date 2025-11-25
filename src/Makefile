GCC = gcc 
CFLAGS = -Wall -Wextra -Werror

test: s21*.c main.c 
	$(GCC) $(CFLAGS) s21*.c main.c -o test -lm

clean:
	rm -rf test