// main read file and write file functions

#ifndef FILEMGR_H
#define FILEMGR_H

#include<vector>

using namespace std;

#include "fs_base.h"
#include "blocks.h"
#include "inode.h"

int writeFile(int disk, char* filename, void* block  );
// int writeFile(int disk, char* filename, void* block , int size );
int readFile(int disk, char*filename, void* block);

int isFileExists(  int disk, char* filename  ) ; 
inode searchFile(int disk, char* filename  ) ;

 void print_FileList(int fileSystemId);

#endif