#include <stdio.h>
#include <unistd.h>
#include <wait.h>
//커널 : 메모리에 항시 상주하는 운영체제의 부분 (= 운영체제)
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


