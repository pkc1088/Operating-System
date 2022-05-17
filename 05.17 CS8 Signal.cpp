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
  //signal(SIGINT, SIG_IGN); 이걸쓰면 ignore돼서 키 안먹힘 
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
CTRL+C 를 입력하게 되면, 현재 실행중인 프로세스에 SIGINT가 전달이 된다. 
SIGINT에 대한 프로세스의 기본행동은 종료이기 때문에, 특별히 시그널을 
제어하지 않을 경우 프로그램은 종료가 된다. 그러나 위에서는 signal함수를 
이용해서 SIGINT에 대해서 sig_handler라는 함수를 실행하도록 했다. 
이제 CTRL+C를 입력하게 되면, 프로세스가 종료되는 대신 sig_handler를 
실행하는걸 확인할 수 있을 것이다.
위 예에서는 시그널함수를 실행시키도록 하고 있는데, 시그널을 무시하거나
 시그널의 기본행동으로 되돌아가도록 할 수도 있다. 이경우 sig_handler 
 대신에 SIG_IGN과 SIG_DFL을 이용하면 된다.
SIG_IGN : 시그널을 무시한다.
SIG_DFL : 기본행동을 하도록 한다.

그렇다면 SIG_DFL은 언제 사용되는가 ? 
fork(2)를 이용해서 자식프로세스를 생성하면, 자식프로세스는 부모의 
시그널정책까지를 그대로 복사해서 사용하게 된다. 즉 부모의 특정 
시그널에 정책이 SIG_IGN 이였다면, 자식도 그대로 그 정책을 따른다. 
때로, 자식의 시그널 정책을 달리할 필요가 있을 것이다. 이 경우 사용
할 수 있다.
*/
