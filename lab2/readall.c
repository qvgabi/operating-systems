#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

ssize_t readall(int fd, const void *buf, size_t nbyte){
    ssize_t nread=0,n;
    do{
        if(n=read(fd,&((const char *)buf)[nread],nbyte-nread)==-1){
            if(errno==EINTR){
                continue;
            }else{
                exit(EXIT_FAILURE);
            }
        }
        
        if(n=='\0'){ //end of line sign
            return nread;
        }
        nread+=n;
    }while(nread<nbyte);
    return nread;
}