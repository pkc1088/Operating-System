#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main() {
    
    pid_t pid;
    pid = fork();   //fork a child process

    if(pid < 0) {
        fprintf(stderr, "fork failed\n");
        return 1;
    } 
    else if(pid == 0) { //child process
        execlp("/bin/ls", "ls", NULL);      //ls 라는 명령어 실행
        printf("\n");
    }
    else {              //parent (pid > 0)
        wait(NULL);     //wait 안해주면 child process 안 기다리고 먼저출력함
        printf("Child Complete\n");
    }
    // exit() 코드로 종료시킬수 있는데 자식이 안끝나는데 부모를 종료시키면 orphan process
    // 부모가 종료되진 않았으나 그냥 진행되면 zombie process가 됨

    return 0;
}
