
CC = 		../../ASM

TARGET = 	out.gen

LIB =		lib/utils.x \
		lib/interactions.x

SRC =		cell.x \
		nucleus.x \
		link.x \
		axon.x \
		soma.x \
		dendrite.x \

BEGIN =		MAIN

all:
	$(CC) $(BEGIN) $(TARGET) $(SRC) $(LIB)

test:
	$(CC) TEST test.gen test.x $(LIB) dendrite.x axon.x






