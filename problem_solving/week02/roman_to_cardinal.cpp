#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>

using namespace std;

// 숫자를 로마숫자로 변환하는 함수
string intToRoman(int num) {
    string roman = "";
    string symbol[] = { "M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I" };
    int value[] = { 1000,900,500,400,100,90,50,40,10,9,5,4,1 };

    for (int i = 0; i < 13; i++) {
        while (num >= value[i]) {
            num -= value[i];
            roman += symbol[i];
        }
    }
    return roman;
}

int main() {
    bool esc = true;
    while (esc) {
        string input;
        cout << "숫자를 입력하세요: ";
        cin >> input;

        // 입력값이 숫자인지 확인
        bool isNumber = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            cout << "잘못 입력하셨습니다." << endl;
            continue; // 다시 입력을 받음
        }

        int num = stoi(input);
        if (num < 1 || num > 3999) {
            cout << "1~3999 사이의 숫자를 입력해주세요." << endl;
            continue; // 다시 입력을 받음
        }

        string roman = intToRoman(num);
        cout << num << "을 로마숫자로 변환한 결과: " << roman << endl;

        cout << "다시 숫자를 입력하시겠습니까 ? (esc를 누르면 종료, 그외 키를 입력하면 계속) : " << endl;
        
        for (int i = 0; i < 5; i++) {
            if (_kbhit()) { // 키보드 입력이 있는 경우
                if (_getch() == 27) { // ESC 키를 누른 경우
                    esc = false; // 루프를 종료합니다.
                    break;
                }
                else
                {
                    break;
                }
            }
            i--;
        }
    }

    return 0;
}
