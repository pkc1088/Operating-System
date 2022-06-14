// 1�� �����Ǵ°� ��µǴ°� ������ sleep(1) �����ΰŰ���
//signal condwait �ٽ� �����ϱ�

#include <pthread.h> 
#include <string.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h>
pthread_mutex_t mutex; 
pthread_cond_t cond; 
int data=0; 
int k=0;

void *increase(void *arg){ 
    while(1){ 
        if(k==200)
            exit(0);

        pthread_mutex_lock(&mutex); 
        pthread_cond_signal(&cond); 
        data++; 
        printf("increase data : %d\n", data);
        pthread_mutex_unlock(&mutex); 
        k++;
        //sleep(1);
    } 
} 
void *printData(void *arg){ 
    while(1){ 
        pthread_mutex_lock(&mutex); 
        pthread_cond_wait(&cond, &mutex); 
        printf("print data :%d\n", data); 
        pthread_mutex_unlock(&mutex); 
    } 
} 
int main(int argc, char *argv[]) {
    k = atoi(argv[1]); 
    pthread_t thread1,thread2; 
    pthread_mutex_init(&mutex,NULL); 
    pthread_cond_init(&cond,NULL); 
    pthread_create(&thread1, NULL, increase,NULL); 
    pthread_create(&thread2, NULL, printData,NULL); 
    pthread_join(thread1, NULL); 
    pthread_join(thread2, NULL); 
    return 0;
}
