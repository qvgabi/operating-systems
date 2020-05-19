#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define MAX 512

int main(int argc, char* argv[]){
    int fd1,fd2,nwritten,nread;
    char buf_to_read[MAX];

    char* filename=argv[1];

    int writtensize=10;

    char* buf="12345678901234567890";
    fd1=open(filename,O_RDWR);
    fd2=open(filename,O_RDWR);


    nwritten=write(fd1,buf,writtensize);
    nread=read(fd2,buf_to_read,writtensize);

    printf("%s",buf_to_read);

    close(fd1);
    close(fd2);

    return 0;

    //dwa deskryptory maja swoje wlasne, osobne wskazniki w pliku, 
    //ktore przemieszczaja sie w nim niezaleznie od siebie

}