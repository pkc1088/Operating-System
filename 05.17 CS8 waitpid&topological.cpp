#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <dirent.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

pid_t Fork(void) {
    pid_t pid;

    if((pid = fork()) < 0)
        printf("Fork error");

    return pid;
}

int main() {

    if(Fork() == 0) {
        printf("9");
        fflush(stdout);
    } else {
        printf("0");
        fflush(stdout);
        waitpid(-1, NULL, 0);
    }
    printf("3");
    fflush(stdout);
    printf("6");
    exit(0);
    
    return 0;
} 
