#include <signal.h>
//https://www.joinc.co.kr/w/Site/system_programing/Book_LSP/ch06_Signal
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void sig_handler(int signo);

int main(int argc, char **argv)
{
  int i = 0;
  signal(SIGINT, (void *)sig_handler);
  //signal(SIGINT, SIG_IGN); �̰ɾ��� ignore�ż� Ű �ȸ��� 
  while(1)
  {
    printf("%d\n", i);
    sleep(2);
    i++;
  }
}

void sig_handler(int signo)
{
  printf("I Received SIGINT(%d)\n", SIGINT);
}

/*
CTRL+C �� �Է��ϰ� �Ǹ�, ���� �������� ���μ����� SIGINT�� ������ �ȴ�. 
SIGINT�� ���� ���μ����� �⺻�ൿ�� �����̱� ������, Ư���� �ñ׳��� 
�������� ���� ��� ���α׷��� ���ᰡ �ȴ�. �׷��� �������� signal�Լ��� 
�̿��ؼ� SIGINT�� ���ؼ� sig_handler��� �Լ��� �����ϵ��� �ߴ�. 
���� CTRL+C�� �Է��ϰ� �Ǹ�, ���μ����� ����Ǵ� ��� sig_handler�� 
�����ϴ°� Ȯ���� �� ���� ���̴�.
�� �������� �ñ׳��Լ��� �����Ű���� �ϰ� �ִµ�, �ñ׳��� �����ϰų�
 �ñ׳��� �⺻�ൿ���� �ǵ��ư����� �� ���� �ִ�. �̰�� sig_handler 
 ��ſ� SIG_IGN�� SIG_DFL�� �̿��ϸ� �ȴ�.
SIG_IGN : �ñ׳��� �����Ѵ�.
SIG_DFL : �⺻�ൿ�� �ϵ��� �Ѵ�.

�׷��ٸ� SIG_DFL�� ���� ���Ǵ°� ? 
fork(2)�� �̿��ؼ� �ڽ����μ����� �����ϸ�, �ڽ����μ����� �θ��� 
�ñ׳���å������ �״�� �����ؼ� ����ϰ� �ȴ�. �� �θ��� Ư�� 
�ñ׳ο� ��å�� SIG_IGN �̿��ٸ�, �ڽĵ� �״�� �� ��å�� ������. 
����, �ڽ��� �ñ׳� ��å�� �޸��� �ʿ䰡 ���� ���̴�. �� ��� ���
�� �� �ִ�.
*/
