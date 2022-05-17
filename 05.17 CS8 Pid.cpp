#include <stdio.h>
#include <unistd.h>

int main() {
    
    pid_t p1, p2, p3, p4, p5;
    
    p1 = getpid();
    p2 = getppid();
    p3 = fork();    //2번째 줄에서는 fork이후의 p4와 p5가 자식프로세스의 영향 받음
                    //즉 p4는 자식프로세서인 p3의 pid갖고 p5는 부모인 p1을 받음
                    //이때 p1과 p2는 분기전임으로 값변화 없음
                    //fork함수의 리턴값은 0임  
    p4 = getpid();
    p5 = getppid();  
    
    printf("%d %d %d %d %d\n", p1, p2, p3, p4, p5);
    return 0;
} 

