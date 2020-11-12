CC = gcc
CFLAGS = -Wall -g
#CFLAGS = -g0 -O3

OBJS = buecher.o buecher_func.o
EXE = buecher

${EXE}: ${OBJS}
	${CC} -o $@ ${OBJS}

${OBJS}: buecher_func.h

run: ${EXE}
	./${EXE}

clean:
	/bin/rm -f core *.o ${EXE}

