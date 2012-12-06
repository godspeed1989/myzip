CC=gcc
CFLAGS=-O2

OBJS=./minizip/*.o ./zlib/*.o

all: zlib.dll zlib.a

zlib.dll:
	make -C ./zlib
	make -C ./minizip
	gcc -fPIC -static -shared $(OBJS) -o $@
zlib.a:
	ar -r $@ $(OBJS)

clean:
	rm *.o
