/*
※ execve : execute 프로그램 by argument를 vector(배열)로, 
environment(환경변수)도 변경하면서.

 exec계열함수는 execve(2)만 system call함수이며, 나머지 execl(3), 
 execlp(3), execle(3), execv(3), execvp(3), execvpe(3)는 execve(3)의 
 wrapping한 함수입니다.

출처: https://www.it-note.kr/157 [IT 개발자 Note]
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
	/* 명령어를 ls로 변경 */ 
	new_argv[0] = command; 
	/* command line으로 넘어온 parameter를 그대로 사용 */ 
	for(idx = 1; idx < argc; idx++) { 
		new_argv[idx] = argv[idx]; 
	} 
	/* argc를 execve 파라미터에 전달할 수 없기 때문에 NULL이 
	파라미터의 끝을 의미함 */ 
	new_argv[argc] = NULL; 
	
	if(execve("/usr/bin/ls", new_argv, environ) == -1) { 
		fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno)); 
		return 1; 
	} 
	
	/* ls 명령어 binary로 실행로직이 교체되었으므로 이후의 로직은 절대 실행되지 않습니다. */ 
	printf("이곳이 이제 ls 명령어라 이 라인은 출력이 되지 않습니다.\n"); 
	return 0; 
} //ls -al 한 것과 같음

/*
함수 이름	프로그램 지정	명령라인 인수	함수 설명
execl	디렉토리와 파일 이름이 합친 전체 이름	인수 리스트	환경 설정 불가
execlp	파일 이름	인수 리스트	환경 설정 불가
execle	디렉토리와 파일 이름이 합친 전체 이름	인수 리스트	환경 설정 가능
execv	디렉토리와 파일 이름이 합친 전체 이름	인수 배열	환경 설정 불가
execvp	파일 이름	인수 배열	환경 설정 불가
excve	전제 경로 명	인수 배열	환경 설정 가능
*/ 


