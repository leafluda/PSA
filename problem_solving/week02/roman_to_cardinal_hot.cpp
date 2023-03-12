#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

// 로마 숫자를 숫자로 변환하는 함수
int romanToDecimal(string romanNumeral) {
    int decimalNum = 0;
    for (int i = 0; i < romanNumeral.length(); i++) {
        // 로마 숫자에 대한 숫자 값을 매핑합니다.
        switch (romanNumeral[i]) {
        case 'I':
            decimalNum += 1;
            break;
        case 'V':
            decimalNum += 5;
            break;
        case 'X':
            decimalNum += 10;
            break;
        case 'L':
            decimalNum += 50;
            break;
        case 'C':
            decimalNum += 100;
            break;
        case 'D':
            decimalNum += 500;
            break;
        case 'M':
            decimalNum += 1000;
            break;
        default:
            return -1; // 잘못된 입력일 경우 -1을 반환합니다.
        }
    }
    return decimalNum;
}

int main() {
    string romanNumeral;
    int decimalNum;
    char key = 'a'; // while문의 조건식이 참이 되도록 초기값을 설정합니다.

    while (key != 27) { // ESC 키 입력시 종료
        // 아무 키나 누를 때까지 대기합니다.
        cout << "로마숫자를 입력하시려면 아무 키나 누르세요. (ESC를 누르면 종료합니다.)" << endl;
        while (!_kbhit()) {} // 키 입력 대기
        key = _getch();
        // 로마 숫자 입력 받기
        do {
            cout << "로마 숫자를 입력하세요: ";
            cin >> romanNumeral;
            decimalNum = romanToDecimal(romanNumeral);
            if (decimalNum == -1) {
                cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
            }
        } while (decimalNum == -1);

        // 로마 숫자를 숫자로 변환하여 출력합니다.
        cout << "입력한 로마 숫자 " << romanNumeral << "는(은) " << decimalNum << "입니다." << endl;
    }

    return 0;
}
