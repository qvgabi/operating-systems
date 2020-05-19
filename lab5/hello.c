#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// ----------------------------------------------------------

void *PrintHello(void *arg);
// ----------------------------------------------------------

int main(int argc, char *argv[]){
     pthread_t thread[10];
     int rc;
     for (size_t i = 0; i < 10; i++)
     {
          rc = pthread_create(&thread, NULL, PrintHello, NULL);
     }
     for (size_t i = 0; i < 10; i++)
     {
          pthread_join(thread[i],NULL); //wątek głowny oczekuje na zakończenie kadego
     }
     printf("End of the main thread!\n");
     
     
     if (rc){
          printf("Return code: %d\n", rc);
          exit(-1);
     }
     //sleep(1);
     return 0;
}
// ----------------------------------------------------------

void *PrintHello(void *arg){
     sleep(1);
     printf("Next boring 'Hello World!' version!\n");
     return NULL;
}