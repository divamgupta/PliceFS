#include "filemgr.h"
#include <math.h>

void buffCpy(char * buff1 , int byteOffset1 , char * buff2 , int byteOffset2 , int size)
{
    for(int i=0;i<size ; i++)
    {
        *(buff1 + byteOffset1 + i ) = *(buff2 + byteOffset2 + i);
    }
}

int writeFile(int disk, char* filename, void* block  )
{
    
    if (isFileExists(   disk, filename  )) 
    {
        cout << "The file exists yo!! \n";
        return 0;
    }
    
    int size = strlen((char*) block);
    
    
    int nBlocks =  (int)ceil( (float)size / (float)BLOCK_SIZE  );
    
    cout << "n blocks " << nBlocks << endl;
    char dataBitmap[BLOCK_SIZE];
    
    readData( disk , DATA_BITMAP  , (void *)dataBitmap );
    vector<int> freeBlocks = getFreeBlocks( nBlocks  ,  dataBitmap );
    
    char tempWriteBuffer[BLOCK_SIZE];
    
    for(int i = 0 ; i < freeBlocks.size() ; i++)
    {
        buffCpy( tempWriteBuffer , 0 ,(char *) block , i*BLOCK_SIZE , BLOCK_SIZE );
        writeData(  disk ,  DATA_BLOCK_OFFSET +  freeBlocks[i] , (void * )tempWriteBuffer  );
    }
    
    setBlocksOnBitmap( freeBlocks  ,  dataBitmap   );
    writeData(  disk , DATA_BITMAP , (void *)dataBitmap  ); // write back bitmap
    
    inode I;
    strcpy( I.fName , filename );
    I.fileSize = size;
    I.blocks = freeBlocks;
    
    cout << freeBlocks.size();
    
    printInode(I);
    char inodeBitmap[BLOCK_SIZE];
    readData( disk , INODE_BITMAP  , (void *)inodeBitmap );
    int freeInodeAdd = getFreeBlocks( nBlocks  ,  inodeBitmap )[0];
    setBitmapBit( freeInodeAdd , 1  , inodeBitmap );
    writeData(  disk , INODE_BITMAP , (void *)inodeBitmap  ); // write back bitmap
    writeNthInode( freeInodeAdd ,  I , INODE_BLOCK_OFFSET , disk  );
    cout << "inode written at " << freeInodeAdd << endl;
    
    return 1;
    
}

int readFile(int disk, char*filename, void* block)
{
    if (!(isFileExists(   disk, filename  ))  )
    {
        cout << "the doesnt  exists yo ";
        return 0;
    }
    
    
    inode in = searchFile(disk, filename);
    int size = in.fileSize;
    
    char tempReadBuffer[BLOCK_SIZE];
    
    for(int i = 0 ; i < in.blocks.size() ; i++)
    {
        readData( disk , DATA_BLOCK_OFFSET + in.blocks[i] ,  tempReadBuffer );
        buffCpy( (char *) block , i*BLOCK_SIZE , tempReadBuffer  , 0 , BLOCK_SIZE );
    }
    cout << "Read file:" << endl;
    return 1;
}


int isFileExists(  int disk, char* filename  ) 
{
    char inodeBitmap[BLOCK_SIZE];
    readData( disk , INODE_BITMAP  , (void *)inodeBitmap );
    vector<int> freeInodeBlocks = getFilledBlocks(  inodeBitmap );
    
    inode tempI;
    
    for( int i=0;i<freeInodeBlocks.size() ; i++)
    {
        tempI = readNthInode( freeInodeBlocks[i] ,  INODE_BLOCK_OFFSET  , disk );
        //cout << "inode scanned " << freeInodeBlocks[i] ;
        //printInode(tempI);
        
        if(strcmp(filename , tempI.fName) == 0 )
        {
            return 1;
        }
        
    }
    
    return 0;
    
    
}

inode searchFile(int disk, char* filename  ) 
{
    char inodeBitmap[BLOCK_SIZE];
    readData( disk , INODE_BITMAP  , (void *)inodeBitmap );
    vector<int> freeInodeBlocks = getFilledBlocks(  inodeBitmap );
    
    inode tempI;
    
    for( int i=0;i<freeInodeBlocks.size() ; i++)
    {
        tempI = readNthInode( freeInodeBlocks[i] ,  INODE_BLOCK_OFFSET  , disk );
        //cout << "inode scanned " << freeInodeBlocks[i] ;
        //printInode(tempI);
        
        if(strcmp(filename , tempI.fName) == 0 )
        {
            return tempI;
        }
        
    }
    
    return tempI ;
    
    
}



 void print_FileList(int fileSystemId)
 {
    int disk = fileSystemId;
    char inodeBitmap[BLOCK_SIZE];
    readData( disk , INODE_BITMAP  , (void *)inodeBitmap );
    vector<int> freeInodeBlocks = getFilledBlocks(  inodeBitmap );
    
    inode tempI;
    cout << "Files available in File System are:" << endl;
    for( int i=0;i<freeInodeBlocks.size() ; i++)
    {
        tempI = readNthInode( freeInodeBlocks[i] ,  INODE_BLOCK_OFFSET  , disk );
        //cout << "inode scanned " << freeInodeBlocks[i] ;
        cout << i+1<<" "<< tempI.fName<< endl;
        
    }
    
 }