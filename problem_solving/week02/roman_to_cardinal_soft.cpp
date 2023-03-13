#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h> // _kbhit()와 _getch() 함수 사용을 위한 헤더파일

using namespace std;

// 숫자를 로마숫자로 변환하는 함수
string intToRoman(int num) {
    string roman = "";
    string symbol[] = { "M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I" }; // 각 자리별 로마숫자 기호
    int value[] = { 1000,900,500,400,100,90,50,40,10,9,5,4,1 };  // 각 자리별 숫자 값

    for (int i = 0; i < 13; i++) {
        while (num >= value[i]) { // 현재 자리의 값이 숫자보다 작아질 때까지 반복
            num -= value[i];    // 현재 자리의 값을 숫자에서 빼줌
            roman += symbol[i]; // 로마숫자 기호를 문자열에 추가
        }
    }
    return roman; // 로마숫자로 변환된 문자열 반환
}

// 입력값이 숫자인지 확인하는 함수
bool checkNum(string input) {
    bool isNumber = true;
    for (char c : input) { // 입력값의 모든 문자를 하나씩 검사
        if (!isdigit(c)) { // 숫자가 아닌 문자가 있으면
            isNumber = false; // isNumber를 false로 설정
            break;
        }
    }
    return isNumber;  // 숫자인지 여부를 반환
}

int main() {
    while (true) {
        string input = "";
        cout << "숫자를 입력하세요. (esc키를 누르면 종료): ";

        while (true) {
            while (!_kbhit()) { // 키보드 입력을 대기
            }
            char ch = _getch();  // 키보드 값을 받음
            if (ch == 27) {  // esc키 일 경우 종료
                return 0;
            }
            else if (ch == 13) { // 엔터키 일 경우 입력루프를 나가며 변환
                break;
            }
            else { // 그외 일 경우 입력된 키보드 값을 string에 저장
                cout << ch;
                input = input + ch;
            }
        }

        cout << endl;

        if (!checkNum(input)) { // 입력값이 숫자가 아닌 경우
            cout << "잘못 입력하셨습니다." << endl;
            continue; // 다시 입력을 받음
        }

        int num = stoi(input); // 입력값을 정수로 변환
        if (num < 1 || num > 3999) { // 입력값이 범위를 벗어난 경우
            cout << "1~3999 사이의 숫자를 입력해주세요." << endl;
            continue; // 다시 입력을 받음
        }

        string roman = intToRoman(num); // 입력값을 로마숫자로 변환
        cout << num << "을 로마숫자로 변환한 결과: " << roman << endl;
    }
    return 0;
}
