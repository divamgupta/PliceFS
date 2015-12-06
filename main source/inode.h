// all the inode APIs and functions to extract metadata from inodes

#ifndef INODE_H
#define INODE_H

#include <vector>
#include<iostream>
#include <cstring>

#include "blocks.h"
#include "fs_config.h"

using namespace std;

typedef struct inode inode;

struct inode{
    char fName[32];
    int fileSize;
    vector<int> blocks;
};

void inodeToBytes(inode I , void * data);
inode  bytesToInode( void * data);

int getIntFromBytes( char * data);
void writeIntInBytes( int n , char * data );

void printInode( inode I);

inode readNthInode( int inodeIndex , int firstInodeBlock , int disk );
void writeNthInode( int inodeIndex , inode I ,  int firstInodeBlock , int disk  );

#endif