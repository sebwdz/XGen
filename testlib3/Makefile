
CC = 		../ASM

TARGET = 	out.gen

LIB =		lib/utils.x \
		lib/interactions.x

SRC =		cell.x \
		nucleus.x \
		axon.x \

BEGIN =		MAIN

all:
	$(CC) $(BEGIN) $(TARGET) $(SRC) $(LIB)

test:
	$(CC) TEST test.gen test.x $(LIB)




