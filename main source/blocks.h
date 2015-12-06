// low level functions to read and write blocks

#ifndef BLOCKS_H
#define BLOCKS_H

#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#include "fs_config.h"

int readData( int disk , int blockNum , void* block );
int writeData( int disk , int blockNum , void* block );


#endif