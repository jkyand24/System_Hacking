#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(void) {
  char secret[16] = "secret message";
  char barrier[4] = {};
  char name[8] = {};
  memset(barrier, 0, 4); // 4바이트의 Null임.
  printf("Your name: ");
  read(0, name, 12); 
  // name 배열은 8바이트인데 비해, read를 통해 필요 이상으로 총 12바이트나 읽어들이고 있음. -> 사용자의 입력값이 name을 넘어 barrier 전체로까지 넘칠 수 있는 크기임.
  printf("Your name is %s.", name);
  // 만약 입력값이 12바이트 이상이 되어 barrier의 Null 4바이트가 모두 침범당하면, 
  // name이라는 string을 끝맺는 Null이 사라지고, 바로 다음의 secret string과 연결되어
  // secret string까지도 함께 print되어버림.
}