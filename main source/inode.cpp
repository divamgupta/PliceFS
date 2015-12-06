#include "inode.h"



void printInode( inode I)
{
    cout << "name - "<< I.fName << endl;
    cout << "size -" << I.fileSize << endl;
    
    for(int i=0; i< I.blocks.size() ; i++)
    {
        cout << "block " << i << " " << I.blocks[i] << endl; 
    }
}

void inodeToBytes(inode I , void * data)
{
    char * sP = (char *) data;
    strcpy(sP , I.fName);
    
    writeIntInBytes( I.fileSize , (sP+32)  );
    writeIntInBytes( I.blocks.size() , (sP+32 + 32 )  );
    
    for(int i=0; i< I.blocks.size() ; i++)
    {
        writeIntInBytes( I.blocks[i]  , (sP+32 + 32 + 32 + 32*i)  );
    }
}

inode  bytesToInode( void * data)
{
    inode I;
    char * sP = (char *) data;
    
    strcpy( I.fName , sP);
    
    I.fileSize = getIntFromBytes(sP+32);
    
    int nBlocks = getIntFromBytes(sP+32 + 32 );
    
    for(int i=0;i<nBlocks ; i++)
    {
        I.blocks.push_back(     getIntFromBytes(sP+32 + 32 + 32 + 32*i )    );
    }
    
    return I;
    
}

void writeIntInBytes( int n , char * data )
{
    *((int *) data ) = n ;   
}

int getIntFromBytes( char * data)
{
    return  (int)*((int *) data );
}


void writeNthInode( int inodeIndex , inode I ,  int firstInodeBlock , int disk )
{
    int blockOffset = (inodeIndex%(BLOCK_SIZE / INODE_SIZE ))*INODE_SIZE  ;
    int blockId = firstInodeBlock + inodeIndex/(BLOCK_SIZE / INODE_SIZE );
    
    char blockDump[ BLOCK_SIZE ];
    char inodeDump[INODE_SIZE];
    
    inodeToBytes( I , (void *) inodeDump );
    readData( disk , blockId  , (void *)blockDump );
   
    for(int i=0; i<INODE_SIZE ; i++)  // write inode byte by byte
    {
        blockDump[blockOffset + i] = inodeDump[i];
    }
    writeData( disk , blockId , (void *)blockDump );
    
    
}


inode readNthInode( int inodeIndex , int firstInodeBlock , int disk )
{
    int blockOffset = (inodeIndex%(BLOCK_SIZE / INODE_SIZE ))*INODE_SIZE  ;
    int blockId = firstInodeBlock + inodeIndex/(BLOCK_SIZE / INODE_SIZE );
    
    char blockDump[ BLOCK_SIZE ];
    char inodeDump[INODE_SIZE];
    
    readData( disk , blockId  , (void *)blockDump );
    
    for(int i=0; i<INODE_SIZE ; i++)  // write inode byte by byte
    {
        inodeDump[i] = blockDump[blockOffset + i];
    }
    
    return bytesToInode( (void *)  inodeDump);
     
}