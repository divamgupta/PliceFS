// bitmaps , super block , initialize fs .. etc


#ifndef FS_BASE_H
#define FS_BASE_H

#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#include <unistd.h>
#include <sys/types.h> // for ftruncate
#include <vector>

#include "blocks.h"

using namespace std;


int createSFS( char* filename, int nbytes);


void setBitmapBit( int bitIndex , int bit , char * buff);
int getBitmapBit( int bitIndex  , char * buff);

vector<int> getFreeBlocks( int size ,  char * buff  );
vector<int> getFilledBlocks(   char * buff  );
void setBlocksOnBitmap( vector<int> indexList  ,  char * buff   ); 
void unsetBlocksOnBitmap( vector<int> indexList  ,  char * buff   ); 
void printBitmap(  char * buff , int limit  );
void print_inodeBitmaps(int fileSystemId);
void print_dataBitmaps(int fileSystemId);


#endif