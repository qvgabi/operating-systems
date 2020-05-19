/*
 * copy1.c
 * 
 * based on: 
 *
 * Miscellaneous examples for Chap. 2
 * AUP2, Chap. 2
 *
 * modified by WTA
 */

/*[copy-with-bug]*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define BUFSIZE 512

void copy(char *from, char *to)  /* has a bug */
{
	int fromfd = -1, tofd = -1;
	ssize_t nread;
	char buf[BUFSIZE];
	
	fromfd = open(from, O_RDONLY);
    if(fromfd==-1){
        if(errno==ENOENT){
            perror("No such file");
        }
        else if(errno==EACCES){
            perror("Permission denied");
        }else{
            perror("ERROR");
            exit(EXIT_FAILURE);
        }

    }
	tofd = open(to, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
    if(tofd==-1){
        if(errno==ENOENT){
            perror("No such file");
        }
        else if(errno==EACCES){
            perror("Permission denied");
        }else{
            perror("ERROR");
            exit(EXIT_FAILURE);
        }

    }else{
        if(read(fromfd, buf, sizeof(buf))==-1){
            perror("ERROR");
            exit(EXIT_FAILURE);
        }else{
            while ((nread = read(fromfd, buf, sizeof(buf))) > 0){
                if(write(tofd, buf, nread)==-1){
                    perror("ERROR");
                    exit(EXIT_FAILURE);
                }else{
                    write(tofd, buf, nread);	
                }
            }
	        
            close(fromfd);
	        close(tofd);
	        return;
        }
    }
}

int main(int argc, char **argv){
	if (argc < 3)
	{
		fprintf(stderr,"usage: %s from_pathname to_pathname\n", argv[0]);
        exit(EXIT_FAILURE);
	}
	copy(argv[1], argv[2]);
	return 0;
}