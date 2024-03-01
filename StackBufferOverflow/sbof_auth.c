#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int check_auth(char *password) { // 입력값(= password)을 buffer(= temp)에 담아 인증을 구현하는 함수
    int auth = 0;
    char temp[16];
    
    strncpy(temp, password, strlen(password)); 
    // strncpy: 입력받은 password 중 어떤 길이 (여기서는 strlen(password))만큼을 temp에 복사함.
    // 이때, password의 길이가 temp의 크기보다 크면,
    // password의 일부는 스택에서 temp가 차지한 범위를 넘어감. 
    // 이때, 그 넘친 위치에 만약 중요한 데이터가 있었다면, 이 데이터를 오염시켜버림.
    // 이 코드의 경우: auth가 오염됨. -> 인증되지 않은 경우 auth는 기본값인 0이어야 하는데, 0이 아니게 되어 인증을 통과해버림.
    
    if(!strcmp(temp, "SECRET_PASSWORD"))
        auth = 1;
    
    return auth;
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./sbof_auth ADMIN_PASSWORD\n");
        exit(-1);
    }

    if (check_auth(argv[1]))
        printf("Hello Admin!\n");
    else
        printf("Access Denied!\n");
}