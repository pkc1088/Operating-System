#include <pthread.h>
#include <stdio.h>
#define true 1
#define false 0
//100프로 확실하게 작동되는건 아님 
//gcc -pthread test.c
int turn, sum = 0;
int flag[2];
void *run1(void *param); 
void *run2(void *param);

int main(int argc, char *argv[])
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, run1, NULL);
	pthread_create(&tid2, NULL, run2, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("%d\n", sum);
}

void *run1(void *param) 
{
    int i;
    for(i = 0; i < 100000; i++) {
        flag[0] = true;
        turn = 1;
        while(flag[1] && turn == 1)
            ;
        sum++;
        flag[0] = false;
    }
	pthread_exit(0);
}

void *run2(void *param) 
{
    int i;
    for(i = 0; i < 100000; i++) {
        flag[1] = true;
        turn = 0;
        while(flag[0] && turn == 0)
            ;
        sum--;
        flag[1] = false;
    }
	pthread_exit(0);
}
