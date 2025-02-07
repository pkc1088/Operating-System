#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; /* this data is shared by the thread(s) */

void *runner(void *param); /* the thread */	
// void *  = 반환형이 정해지지 않은 형태 (역참조로 그 값을 사용할 순 없음) 
int main(int argc, char *argv[])
{
pthread_t tid; /* the thread identifier */
pthread_attr_t attr; /* set of attributes for the thread 필수 아님*/

if (argc != 2) {
	fprintf(stderr,"usage: a.out <integer value>\n");
	/*exit(1);*/
	return -1;
}

if (atoi(argv[1]) < 0) {
	fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
	/*exit(1);*/
	return -1;
}

/* get the default attributes */
pthread_attr_init(&attr);

/* create the thread */
pthread_create(&tid,&attr,runner,argv[1]);

/* now wait for the thread to exit */
pthread_join(tid,NULL);

printf("sum = %d\n",sum);
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param) 
{
int i, upper = atoi(param);
sum = 0;

	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}

	pthread_exit(0);
}

//	gcc -pthread test.c
//	./a.out 10 




/*
argv 2개 주는 경우 구현해봄 
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *runner(void *param); 
int main(int argc, char *argv[])
{
pthread_t tid;
pthread_t tidd;
pthread_attr_t attr;

if (argc != 3) {
	fprintf(stderr,"usage: a.out <integer value>\n");
	return -1;
}

if (atoi(argv[1]) < 0 || atoi(argv[2]) < 0) {
	fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
	return -1;
}

pthread_attr_init(&attr);

pthread_create(&tid,&attr,runner,argv[1]);
pthread_create(&tidd,&attr,runner,argv[2]);
pthread_join(tid, NULL);
pthread_join(tidd, NULL);
printf("sum = %d\n",sum);
}


void *runner(void *param) 
{
    int i, upper = atoi(param);
    sum = 0;

	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}
    
    printf("sum = %d\n",sum);
	pthread_exit(0);
}

*/
