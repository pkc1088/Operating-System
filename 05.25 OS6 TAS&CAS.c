boolean test_and_set(boolean *target) {
	boolean rb = *target;
	*target = true;

	return rv;
}

//����

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

//����
/*
ó������ value�� 1�� �ٲٰ� return�� 0���� �޾Ƽ� cs����
�ٸ� ���μ����� �����ϸ� lock(1)�� expect�� 0�� ���� �������� 
return 1�� �ż� while�ȿ� ���� 
*/
while(true) {
	while(comapre_and_swap(&lock, 0, 1) != 0)
		;
		
	//critical section

	lock = 0;
	
	//rremainder section
} 
