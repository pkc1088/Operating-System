#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main() {
    // �θ�� pid ���, �ڽ��� pid 0
    pid_t pid;
    pid = fork();   
    printf("Hello, Process %d!\n", pid);       

    if(pid > 0)
        wait(NULL);    // �θ�� wait Queue�� �� �����
    
    printf("Hello, Process %d!\n", pid);       

    return 0;
}


