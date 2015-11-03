#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "g711codec.h"

int main( int argc, char *argv[] )
{
	if(argc < 3)
	{
		printf("==> Usage:\n\tdecode [src.g711a] [dest.pcm]\n");	
		//printf("==> Usage:\n\tdecode [src.g711u] [dest.pcm]\n");	
		return 0;
	}

	FILE *pInFile = fopen(argv[1], "rb");
	FILE *pOutFile = fopen(argv[2], "wb");
	if (NULL == pInFile || NULL == pOutFile)
	{
		printf("open file failed\n");
		return 0;
	}

    struct stat s_buf;
    int status = 0;
    status = stat( argv[1], &s_buf );
    printf("file_size = %d\n", s_buf.st_size);
	
	int Ret = 0;
	int Read = 0;
    int DataLen = s_buf.st_size;
    printf("datalen = %d, %s, %d\n", DataLen, __func__, __LINE__);

	unsigned char ucInBuff[ DataLen + 1 ];
	unsigned char ucOutBuff[ 2*DataLen + 1 ];
	memset( ucInBuff, 0, sizeof(ucInBuff) );
    memset( ucOutBuff, 0, sizeof(ucOutBuff) );

	Read = fread( ucInBuff, 1, DataLen, pInFile );
	printf("Read = %d, Ret = %d\n", Read, Ret);
	if (Read)
	{
		Ret = G711a2PCM( (char *)ucInBuff, (char *)ucOutBuff, Read, 0 );
		//Ret = G711u2PCM( (char *)ucInBuff, (char *)ucOutBuff, Read, 0 );
		printf("Read = %d, Ret = %d, %s, %d\n", Read, Ret, __func__, __LINE__);
		fwrite( ucOutBuff, 1, Ret, pOutFile );
		memset( ucInBuff, 0, sizeof(ucInBuff) );
		memset( ucOutBuff, 0, sizeof(ucOutBuff) );
	}
	else
	{
		printf("fread error !\n");
		return -1;
	}
	
	fclose(pInFile);
	fclose(pOutFile);
	return 0;
}

