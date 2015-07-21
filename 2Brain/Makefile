
CC = 		../ASM

TARGET = 	out.gen

SRC =		cell.x \
		skl.x \
		nucleuscell.x \
		cytosol.x \
		neuron.x \
		link.x 

INTER =		cell.xss \
		skl.xss \
		nucleuscell.xss \
		cytosol.xss \
		neuron.xss \

BEGIN =		Cell

all:
	$(CC) $(BEGIN) $(TARGET) $(SRC) $(INTER)
	make -C test/
