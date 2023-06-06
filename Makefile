CC = clang
CFLAGS = -g -Wall

matrix: matrix.c
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -f matrix

.PHONY: clean
