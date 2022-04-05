#include <pthread.h>
#include <stdio.h>
//gcc -pthread test.c

//context switch �������� register�� intterupt issue�� 
//���ϴ� ���� �ȳ��ü��� ���� 
//�ڹٿ����� int sum�� ���� �ٸ� ��ü�� ���ϱ� static int ��� �����
//�Ʒ��� ���� ��Ȳ�� �߻��� 
int sum = 0;
void *run1(void *param); 
void *run2(void *param);

int main(int argc, char *argv[])
{
	int i, scope;
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
    for(i = 0; i < 100000; i++)
        sum++;
	pthread_exit(0);
}

void *run2(void *param) 
{
    int i;
    for(i = 0; i < 100000; i++)
        sum--;
	pthread_exit(0);
}
