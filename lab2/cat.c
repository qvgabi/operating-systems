#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int BUFFSIZE=512;

int main(int argc, char* argv[]){
    int fd;
    ssize_t bytes;
    char buf[BUFFSIZE];
    if(argc==1){
        fd=STDIN_FILENO;
    }else{
        fd=open(argv[1],O_RDONLY);
    }

    if(fd==-1){
        perron("ERROR");
        exit(EXIT_FAILURE);
    }

    bytes=read(fd,buf,BUFFSIZE);
    if(bytes==-1){
        perron("ERROR");
        exit(EXIT_FAILURE);
    }else{
        while(bytes>0){
            buf[bytes]='\0';
            printf("%s", buf);

        }

    }

    close(fd);

    return 0;

}