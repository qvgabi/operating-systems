#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

//TO DO

int main(int argc, char** argv){
    pid_t pid;
    int pfd[2];
    int fd=open("dictionary.txt",O_RDONLY);
    

    if(pipe(pfd)==-1){
        perror("Pipe error");
        exit(EXIT_FAILURE);
    }

    pid=fork();

    if(pid<0){
        perror("Fork error");
        exit(EXIT_FAILURE);
    }



}