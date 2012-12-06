#ifndef __UNZIP_H__
#define __UNZIP_H__
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*
 * decompress a zip file
 */
char* decompress(const char *zfin);
void gzcompress(const char *file, const char* filename);

#define MAX_BUFFER (1024*1024*50)

#endif