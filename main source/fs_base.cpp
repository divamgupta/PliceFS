#include "fs_base.h"


int createSFS( char* filename, int nbytes){

    if( access( filename , F_OK ) != -1 ) {
        // file exists
        FILE * fp=fopen( filename , "rb+");
        return fileno(fp) ;
    } else {
        // file doesn't exist
        cout << "creating a new file " << endl;
        FILE *fp=fopen( filename , "w");
        ftruncate(fileno(fp), nbytes );
        fclose(fp);
        fp=fopen( filename , "rb+");
        return fileno(fp) ;
    }
    
}


void setBitmapBit( int bitIndex , int bit , char * buff)
{
    int bitOffset = bitIndex%8;
    int byteIndex = bitIndex/8;
    
    if(bit)
         *(buff + byteIndex) = (char)(( (int)((*(buff + byteIndex)) | (1 << bitOffset )) ));
    else
         *(buff + byteIndex) = (char)(( (int)((*(buff + byteIndex)) & ~(1 << bitOffset )) ));
    
}


int getBitmapBit( int bitIndex  , char * buff)
{
    int bitOffset = bitIndex%8;
    int byteIndex = bitIndex/8;
    
    if( (int)((*(buff + byteIndex)) & (1 << bitOffset )) )
        return 1;
    else
        return 0;
    
    
}


vector<int> getFreeBlocks( int size ,  char * buff  )
{
    vector<int> freeList;
    
    for(int i =0 ; i < BLOCK_SIZE*8 ; i++)
    {
        if(!(getBitmapBit(i , buff ) ))
            freeList.push_back(i);
        
        if(freeList.size() >= size)
            break;
    }
    
    return freeList;
    
}


vector<int> getFilledBlocks( char * buff  )
{
    vector<int> freeList;
    
    for(int i =0 ; i < BLOCK_SIZE*8 ; i++)
    {
        if((getBitmapBit(i , buff ) ))
            freeList.push_back(i);
        
       
    }
    
    return freeList;
    
}

void setBlocksOnBitmap( vector<int> indexList  ,  char * buff   )
{
    for(int i =0 ; i<indexList.size() ; i++)
    {
        setBitmapBit( indexList[i] , 1 , buff);
    }
}


void unsetBlocksOnBitmap( vector<int> indexList  ,  char * buff   )
{
    for(int i =0 ; i<indexList.size() ; i++)
    {
        setBitmapBit( indexList[i] , 0 , buff);
    }
}

void printBitmap(  char * buff , int limit  )
{
    cout << "Bitmap bits are" << endl;
    for(int i=0; i < limit ; i++)
    {
        cout << getBitmapBit(i,buff) << " ";
    }
    cout << endl;
}

void print_inodeBitmaps(int fileSystemId)
{
    char buff[BLOCK_SIZE];
    cout << "Inode " ;
    readData(fileSystemId,INODE_BITMAP , (void*) buff );
    printBitmap(buff,BLOCK_SIZE);
}

void print_dataBitmaps(int fileSystemId)
{
    char buff[BLOCK_SIZE];
    cout << "Data " ;
    readData(fileSystemId, DATA_BITMAP , (void*) buff );
    printBitmap(buff,BLOCK_SIZE);
}