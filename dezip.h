#ifndef __UNZIP_H__
#define __UNZIP_H__
#include <stdio.h>
#include <string.h>
#include <assert.h>

char* decompress(const char *zfin);

#define MAX_BUFFER (1024*1024*30)


#define MB(x)				(unsigned long)x*1024*1024
#define MAX_IN_FILE_SIZE	(unsigned long)(MB(50))
#define MAX_OUT_FILE_SIZE	(unsigned long)(MB(100))

#endif
