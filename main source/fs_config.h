// All the parameters such as no of inodes, block size ... etc


#ifndef FS_CONFIG_H
#define FS_CONFIG_H

#define BLOCK_SIZE 4069 // in no ofbytes
#define INODE_SIZE  512// 32 for file name + 4*nBlocks

#define MASTER_BLOCK_INDEX 0
#define INODE_BITMAP 1
#define DATA_BITMAP 2

#define INODE_BLOCK_OFFSET 3
#define DATA_BLOCK_OFFSET 1024




#endif