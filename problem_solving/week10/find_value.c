#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* format_Sentence에 형식문자가 종류별로 몇개인지 확인하기 위한 함수 */
int check_Count(char* format_Sentence, int* int_Num, int* string_Num, int* char_Num, int* format_Sequence) {
    char* sentence = format_Sentence;
    int index = 0;

    while ((sentence = strchr(sentence, '%')) != NULL) { // 문자열의 첫번째 위치부터 끝까지 확인 
        switch (*(sentence + 1)) {
        case 's':
            (*string_Num)++; // 각 형식문자에 해당하는 Num을 1씩 올림
            format_Sequence[index] = 1; // 형식문자 순서를 format_Sequence에 저장
            break;

        case 'd':
            (*int_Num)++;
            format_Sequence[index] = 2;
            break;

        case 'c':
            (*char_Num)++;
            format_Sequence[index] = 3;
            break;
        }
        sentence++;
        index++;
    }
    return index;
}

/* sentence의 앞에서부터 n만큼의 문자열을 지우고 나머지 문자열을 앞으로 당기는 함수 */
void remove_Characters(char* sentence, int n) {
    int length = strlen(sentence);

    if (n >= length) {
        // 문자열의 길이보다 크거나 같은 값을 입력한 경우
        // 전체 문자열을 제거
        sentence[0] = '\0';
    }
    else if (n > 0) {
        // n이 0보다 큰 경우
        // n개의 문자를 제거하고 나머지 문자열을 앞으로 당김
        memmove(sentence, sentence + n, length - n + 1);
        sentence[length - n] = '\0';
    }
}

/* sentence에서 substring의 위치를 찾고, sentence의 맨앞부터 substring직전의 위치까지 value에 복사하는 함수 */
void copy_Substring(char* sentence, char* value, char* substring) {
    char* position = strstr(sentence, substring); // substring의 위치를 찾음

    if (position != NULL) { // substring이 존재하는 경우

        int length = position - sentence; // substring 이전까지의 길이 계산
        int substring_Length = strlen(substring);
        if (position == sentence)
        {
            strcpy(value, substring); // sentence 문자열의 일부분을 value에 복사
            value[substring_Length] = '\0'; // 복사한 문자열의 끝을 표시하기 위해 널 문자를 추가
        }
        else {
            strncpy(value, sentence, length); // sentence 문자열의 일부분을 value에 복사
            value[length] = '\0'; // 복사한 문자열의 끝을 표시하기 위해 널 문자를 추가
        }
    }
    else { // substring이 존재하지 않는 경우
        printf("Error : 값문장의 형식이 형식문장과 다릅니다.");
        exit(0);
    }
}

/* sentence에서 substring만 지우는 함수 */
void remove_Substring(char* sentence, char* substring) {
    int length = strlen(substring); // 지우려는 문자열의 길이
    char* position = strstr(sentence, substring); // 지우려는 문자열의 첫 번째 등장 위치

    if (position != NULL) {
        memmove(position, position + length, strlen(position + length) + 1); // 문자열을 당기기
    }
}

/* sentence에서 뒤에서 n번째의 문자가 무엇인지 반환하는 함수 */
char get_last_Character(char* format_Sentence, int n) {
    int i = 0;

    while (format_Sentence[i] != '\0') { // \0위치를 찾음
        i++;
    }
    if (i > 0) { // num번째 전 위치에 있는 문자열을 반환
        return format_Sentence[i - n];
    }
    return '\0'; // 문자열이 비어있을 경우 기본값으로 null 문자 반환
}

/* format_Sentence을 이용해 value_Sentence에서 format_Sequence의 순서에 맞게 형식문자에 해당하는 값을 각 자료형 배열에 저장하는 함수 */
void find_Value(char* format_Sentence, char* value_Sentence, int* format_Sequence, char** s, int* i, char* c, int index) {
    char f_S[1024] = ""; // format_sentence를 저장해서 함수 내에서 사용하기 위해 선언
    char v_S[1024] = ""; // value_sentence를 저장해서 함수 내에서 사용하기 위해 선언
    char value[1024] = ""; // 형식문자에 해당하는 값
    char front[1024] = ""; // 형식문자를 기준으로 앞부분에 해당하는값
    char back[1024] = ""; // 형식문자를 기준으로 다음 형식문자 직전까지 해당하는값
    int s_Index = 0; // 배열에 저장할 때 사용
    int i_Index = 0; // 배열에 저장할 때 사용
    int c_Index = 0; // 배열에 저장할 때 사용
    char last_First = get_last_Character(format_Sentence, 1); // 형식문장의 마지막 문자
    char last_Second = get_last_Character(format_Sentence, 2); // 형식문장의 마지막 직전문자

    strcpy(f_S, format_Sentence); // format_sentence값을 f_s에 저장
    strcpy(v_S, value_Sentence); // value_sentence값을 v_s에 저장

    /* 맨앞에 형식문자가 아닐경우 첫번째 형식문자까지 지움 */
    if (f_S[0] == "%") { // 맨처음 문자가 퍼센트지만
        if (f_S[1] != "s" || f_S[1] != "d" || f_S[1] != "c") { //바로 뒷문자가 형식문자가 아닐경우
            copy_Substring(f_S, front, "%");;
            remove_Substring(f_S, front);
            remove_Substring(v_S, front);
        }
    }
    else { // 맨처음 문자가 퍼센트가 아닐경우
        switch (format_Sequence[0]) {// 다음 형식문자를 확인하고 다음 형식문자 직전의 문자열을 저장
        case 1:
            copy_Substring(f_S, front, "%s");
            break;

        case 2:
            copy_Substring(f_S, front, "%d");
            break;

        case 3:
            copy_Substring(f_S, front, "%c");
            break;
        }
        remove_Substring(f_S, front);
        remove_Substring(v_S, front);
    }

    /* 값 추출 */
    for (int j = 0; j < index; j++) {
        remove_Characters(f_S, 2); // 형식문자 삭제
        if (j < index - 1) {
            switch (format_Sequence[j + 1]) { // 다음 형식문자를 확인하고 다음 형식문자 직전의 문자열을 저장
            case 1:
                copy_Substring(f_S, back, "%s");
                break;

            case 2:
                copy_Substring(f_S, back, "%d");
                break;

            case 3:
                copy_Substring(f_S, back, "%c");
                break;
            }
            remove_Substring(f_S, back); // 형식문자 사이의 문자열까지 지움
            copy_Substring(v_S, value, back); // 형식문자에 해당하는 값 추출
            switch (format_Sequence[j]) { // 해당 형식문자에 해당하는 자료형 배열에 저장
            case 1:
                s[s_Index] = strdup(value);
                s_Index++;
                break;

            case 2:
                i[i_Index] = atoi(value);
                i_Index++;
                break;

            case 3:
                c[c_Index] = value[0];
                c_Index++;
                break;
            }
            strcat(value, back); // 다음 형식문자 직전까지 추출
            remove_Substring(v_S, value); // 다음 형식문자 직전까지 제거         
        }
        else {
            if (last_Second == '%') { // 마지막에서 두번째 문자가 %이고
                if (last_First == 's' || last_First == 'd' || last_First == 'c') { // 마지막문자가 s, d, c일경우 
                    switch (format_Sequence[j]) { // 나머지 문자열을 형식문자에 해당하는 자료형 배열에 저장
                    case 1:
                        s[s_Index] = strdup(v_S);
                        s_Index++;
                        break;

                    case 2:
                        i[i_Index] = atoi(v_S);
                        i_Index++;
                        break;

                    case 3:
                        c[c_Index] = v_S[0];
                        c_Index++;
                        break;
                    }
                }
            }
            else { // 마지막 형식문자 뒤에 문자열이 있을경우
                copy_Substring(v_S, value, f_S); // 형식문자 이후에 문자열을 추출
                switch (format_Sequence[j]) { // 해당 형식문자에 해당하는 자료형 배열에 저장
                case 1:
                    s[s_Index] = strdup(value);
                    s_Index++;
                    break;

                case 2:
                    i[i_Index] = atoi(value);
                    i_Index++;
                    break;

                case 3:
                    c[c_Index] = value[0];
                    c_Index++;
                    break;
                }
            }
        }
    }
}

/* format_Sentence을 검사해서 예외처리 하는 함수 */
int sentence_Test(char* format_Sentence) {
    int i = 0;
    int count = 0;

    while (format_Sentence[i] != '\0') { // 문자열에서 \0를 찾을 때 까지 반복
        if (format_Sentence[i] == '%') {  // 해당 문자가 %일때
            if (format_Sentence[i + 1] != 's' && format_Sentence[i + 1] != 'd' && format_Sentence[i + 1] != 'c') { // 뒤에 s,d,c가 오지않는다면
                printf("Error : 형식문장에 %가 형식문자가 아닌, 단독으로 존재합니다.\n");
                exit(0);
            }
            else if (format_Sentence[i + 2] == '%' && (format_Sentence[i + 3] == 'd' || format_Sentence[i + 3] == 's' || format_Sentence[i + 3] == 'c')) { // 바로 형식문자가 온다면
                if (format_Sentence[i + 1] == format_Sentence[i + 3]) { // 그리고 같은 형식문자가 연달아 나온다면
                    printf("Notify :같은 형식문자가 연달아 나와 두번째 형식문자를 제거합니다.\n");
                    remove_Substring(format_Sentence, (i + 2));
                    count++;
                }
                else {
                    switch (format_Sentence[i + 1]) { // 그리고 형식문자가 연달아 나온다면
                    case 's':
                        printf("Notify : %%s 이후 다른형식문자가 나와 %%s로 통합되어 저장됩니다.\n");
                        remove_Substring(format_Sentence, (i + 2));
                        count++;
                        break;

                    case 'd':
                        printf("Error : %%d 이후 다른형식문자가 존재합니다.\n");
                        exit(0);
                        break;

                    case 'c':
                        printf("Error : %%d 이후 다른형식문자가 존재합니다.\n");
                        exit(0);
                        break;
                    }
                }
            }
        }
        i++;
    }
    return count;
}

/* sentence에서 ""안에 있는 값만 sentence에 다시 저장하는 함수*/
void extract_quoted_Sentences(char* sentence) {
    char* quote_Start = strstr(sentence, "\"");
    char* quote_End = NULL;

    if (quote_Start) {
        quote_End = strstr(quote_Start + 1, "\"");
    }

    if (quote_Start && quote_End) {
        char main_Sentence[1024];
        strncpy(main_Sentence, quote_Start + 1, quote_End - quote_Start - 1);
        main_Sentence[quote_End - quote_Start - 1] = '\0';
        strcpy(sentence, main_Sentence);
    }
    else {
        printf("Error: \"\"가 발견되지 않았습니다. 프로그램을 종료합니다.\n");
        exit(0);
    }
}

int main() {
    /*--------------------------------파일 입출력----------------------------------*/

    FILE* file;
    char format_Sentence[1024], value_Sentence[1024]; // 형식문장 저장 문자열, 값문장 저장 문자열

    file = fopen("psa.txt", "r"); // 파일 열기
    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return 1;
    }

    fgets(format_Sentence, sizeof(format_Sentence), file); // 파일에서 첫번째 문장을 읽어옴
    fgets(value_Sentence, sizeof(value_Sentence), file); // 파일에서 두번째 문장을 읽어옴

    extract_quoted_Sentences(format_Sentence); // ""안에있는 값만 문자열로 저장
    extract_quoted_Sentences(value_Sentence); // ""안에있는 값만 문자열로 저장

    printf("형식문장 : %s\n", &format_Sentence);
    printf("  값문장 : %s\n\n", &value_Sentence);

    if (sentence_Test(value_Sentence) > 0) { // 형식문장을 수정시 출력
        printf("\n수정된 형식문장 : %s\n", &format_Sentence);
        printf("         값문장 : %s\n\n", &value_Sentence);
    }

    /*----------------------------------동적할당----------------------------------*/

    int format_Sequence[100]; // 형식문자의 순서 저장
    int int_Num = 0, string_Num = 0, char_Num = 0, j = 0; // 각 형식문자의 개수저장 , 반복문을 위한 변수 선언
    int index = check_Count(format_Sentence, &int_Num, &string_Num, &char_Num, format_Sequence);
    char** s = (char**)malloc(string_Num * sizeof(char*)); // %s개수만큼 동적핳당
    for (j = 0; j < string_Num; j++) {
        s[j] = (char*)malloc(1024 * sizeof(char)); // 각각의 문자열 크기는 1024으로 가정
    }
    int* i = (int*)malloc(int_Num * sizeof(int)); // %d개수만큼 동적핳당
    char* c = (char*)malloc(char_Num * sizeof(char)); //%c개수만큼 동적핳당

    /*----------------------------------기능구현----------------------------------*/

    find_Value(format_Sentence, value_Sentence, format_Sequence, s, i, c, index); // 형식문자에 해당하는 값 찾기

    printf("int(% d개) :", int_Num); // %d에 해당하는 값 출력
    for (j = 0; j < int_Num; j++) {
        if (j == (int_Num - 1)) {
            printf(" %d\n", i[j]);
        } else {
            printf(" %d,", i[j]);
        }
    }
    printf("char(%d개) :", char_Num); // %c에 해당하는 값 출력
    for (j = 0; j < char_Num; j++) {
        if (j == (char_Num - 1)) {
            printf(" %c\n", c[j]);
        } else {
            printf(" %c,", c[j]);
        }
    }
    printf("string(%d개) :", string_Num); // %s에 해당하는 값 출력
    for (j = 0; j < string_Num; j++) {
        if (j == (string_Num - 1)) {
            printf(" %s\n", s[j]);
        } else {
            printf(" %s,", s[j]);
        }
    }

    /*---------------------------메모리 해제 및 파일닫기--------------------------*/

    for (j = 0; j < string_Num; j++) { // 문자열에 해당하는 메모리 해제
        free(s[j]);
    }
    free(s); // 배열에 해당하는 메모리 해제
    free(i); // 배열에 해당하는 메모리 해제
    free(c); // 배열에 해당하는 메모리 해제
    fclose(file); // 파일 닫기

    return 0;
}
