#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int val = 5; //p0에 있던게 p1으로 복사해서 감 

int main() {
    // 부모는 pid 양수, 자식은 pid 0
    pid_t pid;
    pid = fork();   
   
    if(pid == 0) {
        val += 15;
        return 0;      // 자식은 15 더해주지만 종료된 후 
                       //부모는 그냥 5값 그대로 갖음 (영향 x) 
    }

    if(pid > 0) {
        wait(NULL);    // 부모는 wait Queue에 들어가 대기중
        printf("Parent : val = %d\n", val);       
    }
        
    
    return 0;
}
