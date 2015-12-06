#include "blocks.h"

int readData( int disk , int blockNum , void* block )
{
    FILE* fp = fdopen(disk, "rb+");
    fseek ( fp , BLOCK_SIZE*blockNum , SEEK_SET );
    for(int i=0; i < BLOCK_SIZE ; i++)
    {
         *((char *)block + i) = fgetc(fp);
    }
    
    fflush(fp);
    
    return BLOCK_SIZE;
     
}


int writeData( int disk , int blockNum , void* block )
{
    FILE* fp = fdopen(disk, "rb+");
    fseek ( fp , BLOCK_SIZE*blockNum , 0  );
    for(int i=0; i < BLOCK_SIZE ; i++)
    {
        fputc(   *((char *)block + i)   , fp );
    }
    
    fflush(fp);
    return BLOCK_SIZE;
}