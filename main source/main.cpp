#include <iostream>
#include <cstring>
#include "fs_base.h"
#include "fs_config.h"
#include "blocks.h"
#include "inode.h"
#include<stdio.h>
#include <vector>
#include "filemgr.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 2){
        cout <<"--------Welcome to 'plisfs' File System-----------\n";
        cout << "new filename filesize: To create new file system\nwritefile filename fsname data: To write into file\n";
        cout << "read filename fsname: To read from file\n";
        cout << "bitmap inode fsname: To print bitmaps of inode\n";
        cout << "bitmap data fsname: To print bitmaps of data\n";
        cout << "ls fsname: To list all files registered on file system\n";
    }
    else if( argc == 3 ) {
        if(strcmp(argv[1],"ls")==0)
        {
            int f =  createSFS( argv[2] , BLOCK_SIZE * 32552   );
            print_FileList( f);
        }
      printf("The argument supplied is %s\n", argv[1]);
   }
   else if( argc == 4 ) {
       if(strcmp(argv[1],"new")==0)
        {
            long long int n,a;
            n = atoi(argv[3]);
            if(n>=(BLOCK_SIZE*2048)){
                int f =  createSFS(argv[2] ,  n  );
            }
            else{
                cout << "Insufficient File Size for File System" << endl;
            }
            
        }
        else if(strcmp(argv[1],"read")==0)
        {
            char readbuffer[100000];
             int f =  createSFS( argv[3] , BLOCK_SIZE * 32552   );
             readFile(f,argv[2],(void*)readbuffer);
             cout << readbuffer << endl;
        }
        else if((strcmp(argv[2],"inode")==0)     && (strcmp(argv[1],"bitmap")==0))
        {
            int f =  createSFS( argv[3] , BLOCK_SIZE * 32552   );
             print_inodeBitmaps(f);
        }
        else if((strcmp(argv[2],"data")==0)     && (strcmp(argv[1],"bitmap")==0))
        {
            int f =  createSFS( argv[3] , BLOCK_SIZE * 32552   );
              print_dataBitmaps(f);
        }
      
   }
   
   else if(argc == 5)
   {
        if(strcmp(argv[1],"writefile")==0)
        {
            char writebuffer[100000];
            int f =  createSFS( argv[3] , BLOCK_SIZE * 32552   );
            strcpy(writebuffer , argv[4]);
            writeFile(f,argv[2],(void *)writebuffer);
        }
        //cout << "File has been created and written\n";
   }
   else{
       cout << "Error in arguments given"<< endl;
   }
    
    /*
        plicefs new filename filesize 
        plicefs writefile filename fsname  data
        plicefs read filename fsname
        plicefs bitmap inode fsname
        plicefs bitmap data fsname
        plicefs ls fsname
    */
    
    
}


