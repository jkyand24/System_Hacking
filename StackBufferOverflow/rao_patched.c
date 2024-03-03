#include <stdio.h>
#include <unistd.h>

void get_shell(){
  char *cmd = "/bin/sh";
  char *args[] = {cmd, NULL};

  execve(cmd, args, NULL);
}

int main(){
  char buf[0x28];

  printf("Input: ");
  scanf("%39s", buf); 
  // scanf: 39(= buf의 크기(40바이트) - 1바이트)만큼의 입력을 받음 (마지막 1바이트는 Null바이트의 자리이기에 남겨둠)
  return 0;
}