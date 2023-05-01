#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int vr_scanf(const char* str, void* a, void* b, void* c, void* d)
{
    char input_str[1024]; // 입력 받은 문자열을 저장할 배열
    char* token; // 구분자로 나누어진 문자열을 가리키는 포인터
    int index = 0; // 지정된 변수를 저장하기 위한 인덱스

    // 입력 받은 문자열을 input_str 배열에 저장합니다.
    gets_s(input_str, sizeof(input_str));

    // 입력 받은 문자열을 구분자를 기준으로 나누어 변수에 저장합니다.
    token = strtok(input_str, "|, ");
    while (token != NULL) {
        if (index == 0) {
            *((int*)a) = atoi(token);
        }
        else if (index == 1) {
            *((char*)b) = token[0];
        }
        else if (index == 2) {
            *((float*)c) = atof(token);
        }
        else if (index == 3) {
            strcpy((char*)d, token);
        }
        else {
            // 입력 받은 변수의 개수가 지정된 개수보다 많을 경우
            return -1;
        }
        index++;
        token = strtok(NULL, "|, ");
    }

    // 입력 받은 변수의 개수가 지정된 개수보다 적을 경우
    if (index < 4) {
        return -1;
    }

    return 0;
}

int main()
{
    int a;
    char b;
    float c;
    char d[1024];

    printf("Enter values: ");

    int result = vr_scanf("%d|%c %f,%s", &a, &b, &c, d);

    if (result == 0) {
        printf("Values entered: %d %c %f %s\n", a, b, c, d);
    }
    else {
        printf("Error\n");
    }

    return 0;
}
