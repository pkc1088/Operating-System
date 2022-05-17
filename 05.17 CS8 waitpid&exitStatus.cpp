#define N 2
void unix_error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
pid_t Fork(void) {
    pid_t pid;

    if((pid = fork()) < 0)
        printf("Fork error");

    return pid;
}

int main() {

    int status, i;
    pid_t pid[N], retpid;

    for (i = 0; i < N; i++) 
	    if ((pid[i] = Fork()) == 0) 
	        exit(100+i);

    /* Parent reaps N children in order */
    i = 0;
    while ((retpid = waitpid(pid[i++], &status, 0)) > 0) { 
	    if (WIFEXITED(status))  
	        printf("child %d terminated normally with exit status=%d\n",
		            retpid, WEXITSTATUS(status));
	    else
	        printf("child %d terminated abnormally\n", retpid);
    }
    
    /* The only normal termination is if there are no more children */
    if (errno != ECHILD) 
	    unix_error("waitpid error");

    exit(0);
}

//100�� ���� ����� ���� 101�� ���� �� ���� �ִ�
//��������� û�ҵǴµ� ������ �� �� ���ٴ� ���� �߿� 
