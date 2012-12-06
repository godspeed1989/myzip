#include <stdio.h>
#include <stdlib.h>
#include "dezip.h"
#include "zlib/unzip.h"
#include "zlib/zlib.h"

#define SUFFIX ".gz"
int main(int argc, const char* argv[])
{
	char *name;
	FILE *fin;
	char filename[MAX_PATH];
	if(argc < 2)
	{
		printf("Unzip: args is to few\n");
		return -1;
	}
	strcpy(filename, argv[1]);
	strcat(filename, SUFFIX);
	printf("Compressing '%s' ...\n", argv[1]);
	gzcompress(argv[1], filename);
	printf("Extracting '%s' ...\n", filename);
	name = decompress(filename); // extract the zip file
	if(name) printf("[%s] is decompressed from [%s]\n", name, argv[1]);
	return 0;
}

void gzcompress(const char *file, const char * filename)
{
	FILE * fin;
	void * buf;
	size_t size, temp;
	
	gzFile gzfile;
	fin = fopen(file, "rb");
	fseek(fin, 0, SEEK_END);
	size = ftell(fin);
	printf("Input file size %d\n", size);
	buf = malloc(size);
	rewind(fin);
	fread(buf, 1, size, fin);
	gzfile = gzopen(filename, "wb");
	temp = gzwrite(gzfile, buf, size);
	printf("Write size %d\n", temp);
	size = gzflush(gzfile, Z_FINISH);
	if(size != Z_OK)
		printf("Doomed!\n");
	free(buf);
	gzclose(gzfile);
}

char* decompress(const char *zfin)
{
	FILE *fin, *fout;
	unsigned char * buf;
	unsigned long size, nReadBytes;
	unsigned char signature[4];
	static unsigned char szCurrentFile[MAX_PATH];
	assert(zfin != NULL);
	/* open and detect file type */
	fin = fopen(zfin, "rb");
	if(!fin)
	{
		printf("Unzip: file [%s] open error\n", zfin);
		return NULL;
	}
	fread(signature, 1, 4, fin);
	if( signature[3] == 0x04 && signature[2] == 0x03 &&
		signature[1] == 0x4b && signature[0] == 0x50 )
	{
		int ret;
		unzFile unZipDir;
		unz_file_info unZipFileInfo;
		printf("Unzip: [%s] is a zip file\n", zfin);
		unZipDir = unzOpen(zfin);
		if(unZipDir == NULL)
		{
			printf("Unzip: can't uncompress %s\n", zfin);
			return NULL;
		}
		ret = unzGoToFirstFile(unZipDir);
		while(ret == UNZ_OK)
		{
			ret = unzGetCurrentFileInfo(unZipDir, &unZipFileInfo,
										szCurrentFile, MAX_PATH, NULL, 0, NULL, 0);
			if(ret)
			{
				printf("Unzip: get file info error\n");
				return NULL;
			}
			else if(szCurrentFile[strlen(szCurrentFile)-1] == '/')
			{
				printf("[./%s]\n", szCurrentFile);
				mkdir(szCurrentFile);
			}
			else
			{
				size = unZipFileInfo.uncompressed_size;
				printf(" ./%s -> %d\n", szCurrentFile, size);
				buf = malloc(size);
				assert(buf != NULL);
				if (UNZ_OK == unzOpenCurrentFile(unZipDir))
				{
					nReadBytes = unzReadCurrentFile(unZipDir, buf, size);
					unzCloseCurrentFile(unZipDir);
					fout = fopen(szCurrentFile, "wb");
					assert(fout != NULL);
					fwrite(buf, size, 1, fout);
					fclose(fout);
				}
				free(buf);
			}
			ret = unzGoToNextFile(unZipDir);
		}
		unzClose(unZipDir);
	}
	else if(signature[1] == 0x8b && signature[0] == 0x1f)
	{
		int len;
		char * ptr;
		gzFile gzfile;
		printf("Unzip: [%s] is a gzip file\n", zfin);
		gzfile = gzopen(zfin, "rb");
		if(gzfile == NULL)
		{
			printf("Unzip: can't uncompress %s\n", zfin);
			return NULL;
		}
		buf = malloc(MAX_BUFFER);
		assert(buf != NULL);
		size = gzread(gzfile, buf, MAX_BUFFER);

		len = strlen(zfin);
		ptr = strrchr(zfin, '.');
		if(ptr)
			len = ptr - zfin;
		else
			len -= 1;
		strncpy(szCurrentFile, zfin, len);
		printf("%s -> %d\n", szCurrentFile, size);
		
		fout = fopen(szCurrentFile, "wb");
		assert(fout != NULL);
		fwrite(buf, 1, size, fout);
		fclose(fout);
		gzclose(gzfile);
		free(buf);
	}
	else
	{
		printf("Unzip: file [%s] is not a zip or gzip file\n", zfin);
	}
	return szCurrentFile;
}
