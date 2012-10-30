/*
 * Use minizip to unzip the zip file
 */
#include "dezip.h"
#include "minizip/unzip.h"

int main(int argc, const char* argv[])
{
	FILE *fin;
	if(argc < 2)
	{
		printf("Unzip: args is to few\n");
		return -1;
	}
	fin = fopen(argv[1], "rb");
	if(!fin)
	{
		printf("Unzip: file [%s] open error\n", argv[1]);
		return -1;
	}
	if(!is_zip(fin))
	{
		fclose(fin);
		return 1;
	}
	printf("Unzip: [%s] is a zip file\n", argv[1]);
	fclose(fin);
	decompress(argv[1]);
	return 0;
}

int is_zip(FILE * fin)
{
	unsigned int signature = 0;
	assert(fin != NULL);
	fread(&signature, sizeof(signature), 1, fin);
	if(signature == 0x04034b50)
		return 1;
	else
		return 0;
}

void decompress(const char *zfin)
{
	int ret;
	unzFile unZipDir;
	unz_file_info unZipFileInfo;
	FILE *fout;
	unsigned char * buf;
	unsigned long size, nReadBytes;
	unsigned char szCurrentFile[MAX_PATH];
	unZipDir = unzOpen(zfin);
	if(unZipDir == NULL)
	{
		printf("Unzip: can't uncompress %s\n", zfin);
		exit(-1);
	}
	ret = unzGoToFirstFile(unZipDir);
	while(ret == UNZ_OK)
	{
		ret = unzGetCurrentFileInfo(unZipDir, &unZipFileInfo,
									szCurrentFile, MAX_PATH, NULL, 0, NULL, 0);
		if(ret)
		{
			printf("Unzip: get file info error\n");
			break;
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
