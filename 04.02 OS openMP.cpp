#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	/* sequential code */
	
	// omp_set_num_threads(4) �ϸ� ������ 4�� ���� 
	#pragma omp parallel
	{
		printf("I am a parallel region\n");
	}

	/* sequential code */

	return 0;
}

// compiler�� parallel �ϰ� ó���ϵ��� ������ 
