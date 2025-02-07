#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

int sum = 0;
void *counter(void *param); 
sem_t sem;

int main(int argc, char *argv[]) {
	pthread_t tid[5];
	sem_init(&sem, 0, 5); // 5�� �ƴ϶� 1�̸� ���ؽ����� ���� 
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

//sum�̶�� instance�ϳ��� 5���� �����尡 �����ϴϱ�
//�ᱹ ���̽������ �״�� �߻�
//�����ڿ��� �����Ƿ� ���ϴ°��� �ȳ����µ� 
//sum[5]�� ���� 
