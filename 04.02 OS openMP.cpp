#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	/* sequential code */
	
	// omp_set_num_threads(4) 하면 쓰레드 4개 생성 
	#pragma omp parallel
	{
		printf("I am a parallel region\n");
	}

	/* sequential code */

	return 0;
}

// compiler가 parallel 하게 처리하도록 지시함 
