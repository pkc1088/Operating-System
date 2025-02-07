boolean test_and_set(boolean *target) {
	boolean rb = *target;
	*target = true;

	return rv;
}

//사용법

do {
	while(test_and_set(&lock))
		;
	
	//critical section
	
	lock = false;
	
	//remainder section
} while(true)


int compare_and_swap(int *value, int expected, int new_value) {
	int temp = *value;
	if(*value == expected)
		*value = new_value;
	
	return temp;
}

//사용법
/*
처음에는 value를 1로 바꾸고 return을 0으로 받아서 cs진입
다른 프로세스가 접근하면 lock(1)이 expect의 0과 같지 않음으로 
return 1이 돼서 while안에 갖힘 
*/
while(true) {
	while(comapre_and_swap(&lock, 0, 1) != 0)
		;
		
	//critical section

	lock = 0;
	
	//rremainder section
} 
