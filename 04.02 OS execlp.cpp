#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int val = 5;

int main() {
   
    printf("this\n");
    pid_t pid;
    pid = fork();
    if(pid == 0) {
        execlp("/bin/ls", "ls", NULL);      //p1�� ��ɾ� ls�� �������� ��
        printf("hey");                      //�׷��ԵǸ� hey�� ����Ʈ �ȵ�
    } else if(pid > 0) {
        wait(NULL);
        printf("Child completed, %d\n", getpid());
    }

    return 0;
}

