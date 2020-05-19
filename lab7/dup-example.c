#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
        int     pfd[2];
        pid_t   pid;
        char    string[] = "Test";
        char    buf[10];

        if(pipe(pfd)==-1){
                perror("Pipe error");
                exit(EXIT_FAILURE);
        }

        pid = fork();

        if(pid == 0) {
		close(0);   
                // close(0) jest uzyta do zamkniecia standardowego wejscia, zeby móc mu przypisac nowy proces jako STDIN_FILENO        
 		
                if(dup2(pfd[0],STDIN_FILENO)==-1){
                        perror("Dup2 error");
                        exit(EXIT_FAILURE);
                }
                read(STDIN_FILENO, buf, sizeof(buf));
                printf("Wypisuje: %s\n", buf);
                close(pfd[0]);
                exit(EXIT_SUCCESS);
        } else {
                close(pfd[0]);
        	write(pfd[1], string, (strlen(string)+1));  
                close(pfd[1]);
                exit(EXIT_SUCCESS);
	}
        
        

        return 0;
}