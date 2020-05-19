#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

int pfd[2];
size_t nread;
char buf[100];
int pid;

pipe(pfd);

char * str ="Ur beautiful pipe example";
// write(pfd[1], str, strlen(str));
// nread=read(pfd[0],buf, sizeof(buf));

switch(pid=fork()){
    case -1:
        exit(EXIT_FAILURE);
    case 0: //child
        close(pfd[1]);
        nread=read(pfd[0],buf,sizeof(buf));
        (nread!=0)?printf("%s (%ld bytes)\n",buf,(long)nread):printf("No data\n");
        close(pfd[0]);
        exit(EXIT_SUCCESS);
    default:
        close(pfd[0]);
        write(pfd[1],str,strlen(str));
        close(pfd[1]);
        exit(EXIT_SUCCESS);

}

return 0;
}