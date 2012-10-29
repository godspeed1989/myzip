#ifndef __UNZIP_H__
#define __UNZIP_H__
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*
 * return 1 if it is a zip file
 */
int is_zip(FILE * fin);
void decompress(const char *zfin);

#define MB(x)				(unsigned long)x*1024*1024
#define MAX_IN_FILE_SIZE	(unsigned long)(MB(50))
#define MAX_OUT_FILE_SIZE	(unsigned long)(MB(100))

#endif
