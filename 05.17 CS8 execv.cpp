/*
�� execve : execute ���α׷� by argument�� vector(�迭)��, 
environment(ȯ�溯��)�� �����ϸ鼭.

 exec�迭�Լ��� execve(2)�� system call�Լ��̸�, ������ execl(3), 
 execlp(3), execle(3), execv(3), execvp(3), execvpe(3)�� execve(3)�� 
 wrapping�� �Լ��Դϴ�.

��ó: https://www.it-note.kr/157 [IT ������ Note]
*/

#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
extern char **environ; 
int main(int argc, char *argv[]) { 
	char **new_argv; 
	char command[] = "ls"; 
	int idx; 
	new_argv = (char **)malloc(sizeof(char *) * (argc + 1)); 
	/* ��ɾ ls�� ���� */ 
	new_argv[0] = command; 
	/* command line���� �Ѿ�� parameter�� �״�� ��� */ 
	for(idx = 1; idx < argc; idx++) { 
		new_argv[idx] = argv[idx]; 
	} 
	/* argc�� execve �Ķ���Ϳ� ������ �� ���� ������ NULL�� 
	�Ķ������ ���� �ǹ��� */ 
	new_argv[argc] = NULL; 
	
	if(execve("/usr/bin/ls", new_argv, environ) == -1) { 
		fprintf(stderr, "���α׷� ���� error: %s\n", strerror(errno)); 
		return 1; 
	} 
	
	/* ls ��ɾ� binary�� ��������� ��ü�Ǿ����Ƿ� ������ ������ ���� ������� �ʽ��ϴ�. */ 
	printf("�̰��� ���� ls ��ɾ�� �� ������ ����� ���� �ʽ��ϴ�.\n"); 
	return 0; 
} //ls -al �� �Ͱ� ����

/*
�Լ� �̸�	���α׷� ����	��ɶ��� �μ�	�Լ� ����
execl	���丮�� ���� �̸��� ��ģ ��ü �̸�	�μ� ����Ʈ	ȯ�� ���� �Ұ�
execlp	���� �̸�	�μ� ����Ʈ	ȯ�� ���� �Ұ�
execle	���丮�� ���� �̸��� ��ģ ��ü �̸�	�μ� ����Ʈ	ȯ�� ���� ����
execv	���丮�� ���� �̸��� ��ģ ��ü �̸�	�μ� �迭	ȯ�� ���� �Ұ�
execvp	���� �̸�	�μ� �迭	ȯ�� ���� �Ұ�
excve	���� ��� ��	�μ� �迭	ȯ�� ���� ����
*/ 


