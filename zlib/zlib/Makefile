CC=gcc

all: adler32.o compress.o crc32.o deflate.o gzclose.o gzlib.o \
	gzread.o gzwrite.o infback.o inffast.o inflate.o inftrees.o \
	trees.o uncompr.o zutil.o

adler32.o: adler32.c zutil.h zlib.h zconf.h
compress.o: compress.c zlib.h zconf.h
crc32.o: crc32.c zutil.h zlib.h zconf.h crc32.h
deflate.o: deflate.c deflate.h zutil.h zlib.h zconf.h
gzclose.o: gzclose.c gzguts.h zlib.h zconf.h
gzlib.o: gzlib.c gzguts.h zlib.h zconf.h
gzread.o: gzread.c gzguts.h zlib.h zconf.h
gzwrite.o: gzwrite.c gzguts.h zlib.h zconf.h
infback.o: infback.c zutil.h zlib.h zconf.h inftrees.h inflate.h inffast.h inffixed.h
inffast.o: inffast.c zutil.h zlib.h zconf.h inftrees.h inflate.h inffast.h
inflate.o: inflate.c zutil.h zlib.h zconf.h inftrees.h inflate.h inffast.h inffixed.h
inftrees.o: inftrees.c zutil.h zlib.h zconf.h inftrees.h
trees.o: trees.c deflate.h zutil.h zlib.h zconf.h trees.h
uncompr.o: uncompr.c zlib.h zconf.h
zutil.o: zutil.c zutil.h zlib.h zconf.h
