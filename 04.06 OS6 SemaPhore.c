#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

int sum = 0;
void *counter(void *param); 
sem_t sem;

int main(int argc, char *argv[]) {
	pthread_t tid[5];
	sem_init(&sem, 0, 5); // 5가 아니라 1이면 뮤텍스락과 동일 
    for(int i = 0; i < 5; i++)
        pthread_create(&tid[i], NULL, counter, NULL);
    for(int i = 0; i < 5; i++)
        pthread_join(tid[i], NULL);
    printf("sum = %d\n", sum);
}

void *counter(void *param) {
    for(int i = 0; i < 100000; i++) {
        sem_wait(&sem);
        sum++;
        sem_post(&sem); //notify, in java 
    }
	pthread_exit(0);
}

//sum이라는 instance하나에 5개의 스레드가 접근하니깐
//결국 레이스컨디션 그대로 발생
//공유자원이 있으므로 원하는값이 안나오는듯 
//sum[5]면 노상관 
