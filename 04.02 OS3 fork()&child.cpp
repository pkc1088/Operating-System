#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int val = 5;

int main() {
    
    pid_t pid;
   
    for (int i = 0; i < 3; i++) {
        pid = fork();
        val += 5;
        printf("pid : %d, val : %d\n", pid, val);
    }
    
    return 0;
}
/*
pid : 1346, val : 10
pid : 0, val : 10
pid : 1347, val : 15
pid : 0, val : 15
pid : 1349, val : 20
pid : 1348, val : 15
pid : 0, val : 15
pid : 0, val : 20
pid : 1351, val : 20
pid : 1350, val : 20
pid : 0, val : 20
pid : 0, val : 20
pid : 1352, val : 20
pid : 0, val : 20
*/
