#include <stdio.h>
#include <unistd.h>
#include <wait.h>


int main() {
   
    pid_t pid1, pid2;

    printf("%d %d %d\n", pid1, pid2, getpid());

    pid1 = fork();
    
    printf("%d %d %d\n", pid1, pid2, getpid());

    if(pid1 == 0) {     //child
        pid2 = getpid();
        printf("child : pid1 = %d\n", pid1);
        printf("child : pid2 = %d\n", pid2);
    } else if(pid1 > 0) {   //parent
        pid2 = getpid();
        printf("parent : pid1 = %d\n", pid1);
        printf("parent : pid2 = %d\n", pid2);
        wait(NULL);
        printf("waited\n");
    }

    return 0;
} 

