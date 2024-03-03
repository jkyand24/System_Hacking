#include <stdio.h>
#include <unistd.h>

void init() {
  setvbuf(stdin, 0, 2, 0); // setvbuf(FILE 구조체에 대한 포인터, 버퍼, 버퍼링 모드, 버퍼 크기(바이트))
  setvbuf(stdout, 0, 2, 0);
}

void get_shell() {
  char *cmd = "/bin/sh";
  char *args[] = {cmd, NULL};

  execve(cmd, args, NULL);
}

int main() {
  char buf[0x28];

  init();

  printf("Input: ");
  scanf("%s", buf); 
  // 입력값의 크기를 확인하지 않고 있다. -> buf 크기보다 큰 것이 들어오면 overflow 발생

  return 0;
}