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
        execlp("/bin/ls", "ls", NULL);      //ls ��� ��ɾ� ����
        printf("\n");
    }
    else {              //parent (pid > 0)
        wait(NULL);     //wait �����ָ� child process �� ��ٸ��� ���������
        printf("Child Complete\n");
    }
    // exit() �ڵ�� �����ų�� �ִµ� �ڽ��� �ȳ����µ� �θ� �����Ű�� orphan process
    // �θ� ������� �ʾ����� �׳� ����Ǹ� zombie process�� ��

    return 0;
}
