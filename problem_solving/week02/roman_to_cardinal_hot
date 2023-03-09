#include <iostream>
#include <string>
#include <conio.h> // getch() 함수를 사용하기 위한 헤더 파일

using namespace std;

int toDecimal(char c); // 로마 숫자 하나를 10진수로 변환하는 함수
int romanToDecimal(string s); // 로마 숫자를 10진수로 변환하는 함수

int main() {
    string roman;

    while (true) {
        cout << "로마 숫자를 입력하세요 (ESC 키를 누르면 종료됩니다.): ";
        char ch = getch(); // 키 입력 받기

        if (ch == 27) { // ESC 키가 눌리면 종료
            break;
        }
        else if (ch == '\r') { // Enter 키가 눌리면 로마 숫자 변환 실행
            int decimal = romanToDecimal(roman);

            if (decimal == -1) { // 에러 발생시 -1 반환
                cout << "Error: 잘못된 입력입니다. 로마 숫자를 입력해주세요." << endl;
            }
            else {
                cout << roman << " ==10진수 변환==> " << decimal << endl;
            }

            roman = ""; // 입력된 로마 숫자 초기화
        }
        else { // 로마 숫자 입력 받기
            roman += ch;
            cout << ch;
        }
    }
    return 0;
}

// 로마 숫자를 10진수로 변환하는 함수
int romanToDecimal(string s) {
    int decimal = 0; // 10진수를 저장하는 변수
    int prev = 0; // 이전에 처리한 로마 숫자의 10진수 값
    int current; // 현재 처리하는 로마 숫자의 10진수 값
    int count = 0; // 같은 문자가 연속으로 나오는 횟수를 세는 변수

    for (int i = 0; i < s.length(); i++) {
        current = toDecimal(s[i]); // 현재 글자의 10진수 값 계산

        if (current == -1) { // 로마 숫자가 아닌 글자가 입력된 경우
            return -1;
        }

        if (prev < current) { // 현재 글자가 이전 글자보다 큰 경우
            decimal -= prev;
            decimal += (current - prev);

            // 같은 문자가 연속으로 4번 나오는 경우
            if (count >= 3 && prev == current / 10) {
                return -1;
            }
            count = 1;
        }
        else { // 현재 글자가 이전 글자보다 작거나 같은 경우
            decimal += current;

            // 같은 문자가 연속으로 나오는 경우
            if (prev == current) {
                count++;
                // 같은 문자가 연속으로 4번 나오는 경우
                if (count >= 4) {
                    return -1;
                }
            }
            else {
                count = 1;
            }
        }

        if (decimal >= 4000) { // 3999를 초과하는 로마 숫자가 입력된 경우
            return -1;
        }

        prev = current; // 현재 글자를 이전 글자로 설정
    }

    return decimal;
}

// 로마 숫자를 10진수로 변환하는 함수
int toDecimal(char c) {
    switch (c) {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default: // 로마 숫자가 아닌 경우
        return -1;
    }
}
