#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main() {
    // 부모는 pid 양수, 자식은 pid 0
    pid_t pid;
    pid = fork();   
    printf("Hello, Process %d!\n", pid);       

    if(pid > 0)
        wait(NULL);    // 부모는 wait Queue에 들어가 대기중
    
    printf("Hello, Process %d!\n", pid);       

    return 0;
}


