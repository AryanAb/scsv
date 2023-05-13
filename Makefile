CC = clang
CFLAGS = -Wall -lncurses -g
EXEC = scsv
OBJECTS = src/csv.o src/display.o src/parse.o src/scsv.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
