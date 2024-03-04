#include <stdio.h>
#include <unistd.h>

int main() {
  char buf[0x50];

  printf("Address of the buf: %p\n", buf);
  printf("Distance between buf and $rbp: %ld\n",
         (char*)__builtin_frame_address(0) - buf);

  printf("[1] Leak the canary\n");
  printf("Input: ");
  fflush(stdout); // 이때까지의 stdout 버퍼를 비워 즉시 출력하도록 함

  read(0, buf, 0x100);
  printf("Your input is '%s'\n", buf);

  puts("[2] Overwrite the return address");
  printf("Input: ");
  fflush(stdout); // 이때까지의 stdout 버퍼를 비워 즉시 출력하도록 함
  gets(buf);

  return 0;
}