LIBS=./zlib/zlib.lib
CFLAGS=`pkg-config --cflags minizip`

all: unzip

unzip: unzip.o
	gcc $+ $(LIBS) -o $@

unzip.o: unzip.c dezip.h
	gcc -c $(CFLAGS) $<

run: unzip
	./$< test.zip

clean:
	rm -rf unzip.o 