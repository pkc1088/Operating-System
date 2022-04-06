#include <pthread.h>
#include <stdio.h>
#define true 1
#define false 0

//gcc -pthread test.c
int sum = 0;
void *counter(void *param); 
pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, counter, NULL);
	pthread_create(&tid2, NULL, counter, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("%d\n", sum);

}

void *counter(void *param) 
{
    int i;
    for(i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }
	pthread_exit(0);
}

