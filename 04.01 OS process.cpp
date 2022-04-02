#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int val = 5; //p0�� �ִ��� p1���� �����ؼ� �� 

int main() {
    // �θ�� pid ���, �ڽ��� pid 0
    pid_t pid;
    pid = fork();   
   
    if(pid == 0) {
        val += 15;
        return 0;      // �ڽ��� 15 ���������� ����� �� 
                       //�θ�� �׳� 5�� �״�� ���� (���� x) 
    }

    if(pid > 0) {
        wait(NULL);    // �θ�� wait Queue�� �� �����
        printf("Parent : val = %d\n", val);       
    }
        
    
    return 0;
}
