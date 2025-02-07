#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int val = 5;

int main() {
   
    printf("this\n");
    pid_t pid;
    pid = fork();
    if(pid == 0) {
        execlp("/bin/ls", "ls", NULL);      //p1을 명령어 ls로 덮어씌워라는 뜻
        printf("hey");                      //그렇게되면 hey가 프린트 안됨
    } else if(pid > 0) {
        wait(NULL);
        printf("Child completed, %d\n", getpid());
    }

    return 0;
}

