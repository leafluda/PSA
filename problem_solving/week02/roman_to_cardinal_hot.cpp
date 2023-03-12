#include <iostream>
#include <string>
#include <conio.h> // _kbhit(), _getch() 함수 사용을 위해 추가

using namespace std;

int romanToInt(string s) {
    int result = 0;
    int len = s.length();

    for (int i = 0; i < len; i++) {
        if (s[i] == 'M') {
            result += 1000;
        }
        else if (s[i] == 'D') {
            result += 500;
        }
        else if (s[i] == 'C') { // C다음에 M혹은 D가 올경우를 고려함
            if (i < len - 1 && (s[i + 1] == 'M' || s[i + 1] == 'D')) {
                result -= 100;
            }
            else {
                result += 100;
            }
        }
        else if (s[i] == 'L') {
            result += 50;
        }
        else if (s[i] == 'X') { // X다음에 C혹은 L이 올경우를 고려함
            if (i < len - 1 && (s[i + 1] == 'C' || s[i + 1] == 'L')) {
                result -= 10;
            }
            else {
                result += 10;
            }
        }
        else if (s[i] == 'V') {
            result += 5;
        }
        else if (s[i] == 'I') { // I다음에 X혹은 V가 올경우를 고려함
            if (i < len - 1 && (s[i + 1] == 'X' || s[i + 1] == 'V')) {
                result -= 1;
            }
            else {
                result += 1;
            }
        }
        else {
            cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
            return -1;
        }
    }

    return result;
}

int main() {
    string roman;
    int num;

    while(true) {
        cout << "아무 키나 누르면 계속 입력할 수 있습니다. (esc를 누르면 종료)" << endl;

        while (!_kbhit()) { // 키보드 입력을 대기
        }
        if (_getch() == 27) { // ESC 키를 누르면 종료
            return 0;
        }

        cout << "로마 숫자를 입력하세요: ";
        cin >> roman;

        num = romanToInt(roman);

        if (num == -1) { // 잘못된 입력인 경우 다시 입력
            continue;
        }

        cout << "변환된 숫자: " << num << endl;
    }

    return 0;
}
