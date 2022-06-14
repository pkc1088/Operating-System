// 1씩 증가되는게 출력되는건 순전히 sleep(1) 때문인거같음
//signal condwait 다시 공부하기

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
        pthread_cond_wait(&cond, &mutex);   //wait는 mutex를 unlock시키고 기다리다가 signal 받으면 
        printf("print data :%d\n", data);   //mutex를 lock시키고 다음꺼 실행함 그래서
        pthread_mutex_unlock(&mutex);       //unlock 필수인듯
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
