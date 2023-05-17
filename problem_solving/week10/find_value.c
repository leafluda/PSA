#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 형식문자가 종류별로 몇개인지 확인하기 위한 함수 */
int checkcount(char* format_sentence, int* intNum, int* stringNum, int* charNum, int* format_Sequence) { 
    char* sentence = format_sentence;
    int index = 0;

    while ((sentence = strchr(sentence, '%')) != NULL) { // 문자열의 첫번째 위치부터 끝까지 확인 
        switch (*(sentence + 1)) {
        case 's':
            (*stringNum)++; // 각 형식문자에 해당하는 Num을 1씩 올림
            format_Sequence[index] = 1; // 형식문자 순서를 format_Sequence에 저장
            break;

        case 'd':
            (*intNum)++;
            format_Sequence[index] = 2;
            break;

        case 'c':
            (*charNum)++;
            format_Sequence[index] = 3;
            break;
        }
        sentence++;
        index++;
    }
    return 0;
}

/* str의 앞에서부터 n만큼의 문자열을 지우고 나머지 문자열을 앞으로 당기는 함수 */
void removeCharacters(char* str, int n) { 
    int len = strlen(str);

    if (n >= len) {
        // 문자열의 길이보다 크거나 같은 값을 입력한 경우
        // 전체 문자열을 제거
        str[0] = '\0';
    } else if (n > 0) {
        // n이 0보다 큰 경우
        // n개의 문자를 제거하고 나머지 문자열을 앞으로 당김
        memmove(str, str + n, len - n + 1);
    }
}

/* str n번째 위치부터 2칸만큼의 문자열을 지우고 나머지 문자열을 앞으로 당기는 함수 */
void removelenCharacters(char* str, int n) {
    int len = strlen(str);

    memmove(str + (n), str + (n) + 2, len - (n) - 1);
    str[len - 2] = '\0';
}

/* source에서 substring의 위치를 찾고, source의 맨앞부터 substring직전의 위치까지 destination에 복사하는 함수 */
void copySubstring(char* source, char* destination, const char* substring) { 
    char* position = strstr(source, substring); // substring의 위치를 찾음

    if (position != NULL) { // substring이 존재하는 경우

            int length = position - source; // substring 이전까지의 길이 계산
            int sublen = strlen(substring);
            if (position == source)
            {
                printf("Error : 값문장의 형식이 형식문장과 다릅니다.");
                strcpy(destination, substring); // source 문자열의 일부분을 destination에 복사
                printf("%s\n",destination);
                destination[sublen] = '\0'; // 복사한 문자열의 끝을 표시하기 위해 널 문자를 추가
            } else {
                strncpy(destination, source, length); // source 문자열의 일부분을 destination에 복사
                destination[length] = '\0'; // 복사한 문자열의 끝을 표시하기 위해 널 문자를 추가
            }
    } else { // substring이 존재하지 않는 경우
        printf("Error : 값문장의 형식이 형식문장과 다릅니다.");
        exit(0);
    }
}

/* str에서 sub만 지우는 함수 */
void removeSubstring(char* str, const char* sub) { 
    int len = strlen(sub); // 지우려는 문자열의 길이
    char* pos = strstr(str, sub); // 지우려는 문자열의 첫 번째 등장 위치

    if (pos != NULL) {
        memmove(pos, pos + len, strlen(pos + len) + 1); // 문자열을 당기기
    }
}

/* str에서 뒤에서 num번째의 문자가 무엇인지 반환하는 함수 */
char getLastCharacter(const char* str, int num) { 
    int i = 0;

    while (str[i] != '\0') { // \0위치를 찾음
        i++;
    }
    if (i > 0) { // num번째 전 위치에 있는 문자열을 반환
        return str[i - num];
    }
    return '\0'; // 문자열이 비어있을 경우 기본값으로 null 문자 반환
}

/* format_sentence을 이용해 value_sentence에서 format_Sequence의 순서에 맞게 형식문자에 해당하는 값을 각 자료형 배열에 저장하는 함수 */
void find_value(char* format_sentence, char* value_sentence, int* format_Sequence, char** s, int* i, char* c, int inDex) { 
    char f_s[1024] = ""; // format_sentence를 저장해서 함수 내에서 사용하기 위해 선언
    char v_s[1024] = ""; // value_sentence를 저장해서 함수 내에서 사용하기 위해 선언
    char value[1024] = ""; // 형식문자에 해당하는 값
    char front[1024] = ""; // 형식문자를 기준으로 앞부분에 해당하는값
    char back[1024] = ""; // 형식문자를 기준으로 다음 형식문자 직전까지 해당하는값
    int index = inDex; // 전체 형식문자의 개수   
    int sIndex = 0; // 배열에 저장할 때 사용
    int iIndex = 0; // 배열에 저장할 때 사용
    int cIndex = 0; // 배열에 저장할 때 사용
    char lastChar = getLastCharacter(format_sentence,1); // 형식문장의 마지막 문자
    char last_second = getLastCharacter(format_sentence,2); // 형식문장의 마지막 직전문자

    strcpy(f_s, format_sentence); // format_sentence값을 f_s에 저장
    strcpy(v_s, value_sentence); // value_sentence값을 v_s에 저장

    /* 맨앞에 형식문자가 아닐경우 첫번째 형식문자까지 지움 */
    if (f_s[0] == "%"){ // 맨처음 문자가 퍼센트지만
        if (f_s[1] != "s" || f_s[1] != "d" || f_s[1] != "c"){ //바로 뒷문자가 형식문자가 아닐경우
            copySubstring(f_s, front, "%");;
            removeSubstring(f_s, front);
            removeSubstring(v_s, front);
        }   
    } else { // 맨처음 문자가 퍼센트가 아닐경우
        switch (format_Sequence[0]) {// 다음 형식문자를 확인하고 다음 형식문자 직전의 문자열을 저장
        case 1:
            copySubstring(f_s, front, "%s");
            break;

        case 2:
            copySubstring(f_s, front, "%d");
            break;

        case 3:
            copySubstring(f_s, front, "%c");
            break;
        }
        removeSubstring(f_s, front);
        removeSubstring(v_s, front);
    }

    /* 값 추출 */
    for (int j = 0; j < index; j++){
        removeCharacters(f_s, 2); // 형식문자 삭제
        if (j < index - 1) {
            switch (format_Sequence[j + 1]) { // 다음 형식문자를 확인하고 다음 형식문자 직전의 문자열을 저장
            case 1:
                copySubstring(f_s, back, "%s");
                break;

            case 2:
                copySubstring(f_s, back, "%d");
                break;

            case 3:
                copySubstring(f_s, back, "%c");
                break;
            }
            removeSubstring(f_s, back); // 형식문자 사이의 문자열까지 지움
            copySubstring(v_s, value, back); // 형식문자에 해당하는 값 추출
            switch (format_Sequence[j]) { // 해당 형식문자에 해당하는 자료형 배열에 저장
            case 1:
                s[sIndex] = strdup(value);
                sIndex++;
                break;

            case 2:
                i[iIndex] = atoi(value);
                iIndex++;
                break;

            case 3:
                c[cIndex] = value[0];
                cIndex++;
                break;
            }
            strcat(value, back); // 다음 형식문자 직전까지 추출
            removeSubstring(v_s, value); // 다음 형식문자 직전까지 제거
        } else {
            if (last_second == '%') { // 마지막에서 두번째 문자가 %이고
                if (lastChar == 's'|| lastChar == 'd' || lastChar == 'c') { // 마지막문자가 s, d, c일경우 
                    switch (format_Sequence[j]) { // 나머지 문자열을 형식문자에 해당하는 자료형 배열에 저장
                    case 1:
                        s[sIndex] = strdup(v_s);
                        sIndex++;
                        break;

                    case 2:
                        i[iIndex] = atoi(v_s);
                        iIndex++;
                        break;

                    case 3:
                        c[cIndex] = v_s[0];
                        cIndex++;
                        break;
                    }
                } 
            } else { // 마지막 형식문자 뒤에 문자열이 있을경우
                copySubstring(v_s, value, f_s); // 형식문자 이후에 문자열을 추출
                switch (format_Sequence[j]) { // 해당 형식문자에 해당하는 자료형 배열에 저장
                case 1:
                    s[sIndex] = strdup(value);
                    sIndex++;
                    break;

                case 2:
                    i[iIndex] = atoi(value);
                    iIndex++;
                    break;

                case 3:
                    c[cIndex] = value[0];
                    cIndex++;
                    break;
                }
            }
        }
    }
}

/* 형식문장을 검사해서 예외처리 하는 함수 */
int sentence_test(char* format_sentence) { 
    int i = 0;

    while (format_sentence[i] != '\0') { // 문자열에서 \0를 찾을 때 까지 반복
        if (format_sentence[i] == '%'){  // 해당 문자가 %일때
            if (format_sentence[i + 1] != 's' && format_sentence[i + 1] != 'd' && format_sentence[i + 1] != 'c'){ // 뒤에 s,d,c가 오지않는다면
                printf("Error : 형식문장에 %가 형식문자가 아닌, 단독으로 존재합니다.\n");
                exit(0);
            } else if(format_sentence[i + 2] == '%' && (format_sentence[i + 3] == 'd' || format_sentence[i + 3] == 's' || format_sentence[i + 1] == 'c')) { // 바로 형식문자가 온다면
                if (format_sentence[i + 3] == format_sentence[i + 1]) { // 그리고 같은 형식문자가 연달아 나온다면
                    printf("Notify :같은 형식문자가 연달아 나와 두번째 형식문자를 제거합니다.\n");
                    removelenCharacters(format_sentence, (i + 2));
                    return 1;
                } else { 
                    switch (format_sentence[i + 1]) { // 그리고 형식문자가 연달아 나온다면
                    case 's':
                        printf("Notify : %%s 이후 다른형식문자가 나와 %%s로 통합되어 저장됩니다.\n");
                        removelenCharacters(format_sentence, (i + 2));
                        return 1;
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

    return 0;
}

/* main_sentence에서 ""안에 있는 값만 main_sentence에 다시 저장하는 함수*/
void extractQuotedSentences(char* main_sentence) {
    char sentence[1024];
    char* quoteStart = strstr(main_sentence, "\"");

    if (quoteStart) {
        char* quoteEnd = strstr(quoteStart + 1, "\"");
        if (quoteEnd) {
            strncpy(sentence, quoteStart + 1, quoteEnd - quoteStart - 1);
            sentence[quoteEnd - quoteStart - 1] = '\0';
            strcpy(main_sentence, sentence);
        }
    }
}

int main() {
    /*--------------------------------파일 입출력----------------------------------*/

    FILE* file;
    char temp[1024];
    char format_sentence[1024]; // 형식문장 저장 문자열
    char value_sentence[1024]; // 값문장 저장 문자열

    file = fopen("psa.txt", "r"); // 
    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return 1;
    }

    fgets(format_sentence, sizeof(format_sentence), file);
    fgets(value_sentence, sizeof(value_sentence), file);

    extractQuotedSentences(format_sentence);
    extractQuotedSentences(value_sentence);

    printf("형식문장 : %s\n", &format_sentence);
    printf("  값문장 : %s\n\n", &value_sentence);

    if (sentence_test(format_sentence) == 1){
        printf("\n수정된 형식문장 : %s\n", &format_sentence);
        printf("         값문장 : %s\n\n", &value_sentence);
    }

    /*----------------------------------동적할당----------------------------------*/

    int format_Sequence[100];
    int intNum = 0;
    int stringNum = 0;
    int charNum = 0;

    checkcount(format_sentence, &intNum, &stringNum, &charNum, format_Sequence);
    int index = intNum + stringNum + charNum;
    char** s = (char**)malloc(stringNum * sizeof(char*)); // %s개수만큼 동적핳당
    for (int i = 0; i < stringNum; i++) {
        s[i] = (char*)malloc(1024 * sizeof(char)); // 각각의 문자열 크기는 1024으로 가정
    }
    int* i = (int*)malloc(intNum * sizeof(int)); // %d개수만큼 동적핳당
    char* c = (char*)malloc(charNum * sizeof(char)); //%c개수만큼 동적핳당

    /*----------------------------------기능구현----------------------------------*/

    find_value(format_sentence, value_sentence, format_Sequence, s, i, c, index); // 형식문자에 해당하는 값 찾기

    printf("int(% d개) :", intNum); // %d에 해당하는 값 출력
    for (int j = 0; j < intNum; j++) {
        if (j == (intNum - 1)){
            printf(" %d\n", i[j]);
        } else {
            printf(" %d,", i[j]);
        }
    }
    printf("char(%d개) :", charNum); // %c에 해당하는 값 출력
    for (int j = 0; j < charNum; j++) {
        if (j == (charNum - 1)){
            printf(" %c\n", c[j]);
        } else {
            printf(" %c,", c[j]);
        }
    }
    printf("string(%d개) :", stringNum); // %s에 해당하는 값 출력
    for (int j = 0; j < stringNum; j++) {
        if (j == (stringNum - 1)){
            printf(" %s\n", s[j]);
        } else {
            printf(" %s,", s[j]);
        }
    }

    /*---------------------------메모리 해제 및 파일닫기--------------------------*/

    for (int i = 0; i < stringNum; i++) { // 문자열에 해당하는 메모리 해제
        free(s[i]);
    }
    free(s); // 배열에 해당하는 메모리 해제
    free(i); // 배열에 해당하는 메모리 해제
    free(c); // 배열에 해당하는 메모리 해제
    fclose(file); // 파일 닫기

    return 0;
}
