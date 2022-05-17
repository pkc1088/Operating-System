#include <stdio.h>
#include <unistd.h>

int main() {
    
    pid_t p1, p2, p3, p4, p5;
    
    p1 = getpid();
    p2 = getppid();
    p3 = fork();    //2��° �ٿ����� fork������ p4�� p5�� �ڽ����μ����� ���� ����
                    //�� p4�� �ڽ����μ����� p3�� pid���� p5�� �θ��� p1�� ����
                    //�̶� p1�� p2�� �б��������� ����ȭ ����
                    //fork�Լ��� ���ϰ��� 0��  
    p4 = getpid();
    p5 = getppid();  
    
    printf("%d %d %d %d %d\n", p1, p2, p3, p4, p5);
    return 0;
} 

