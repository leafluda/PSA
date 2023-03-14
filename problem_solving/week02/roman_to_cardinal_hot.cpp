#include <iostream>
#include <string>
#include <conio.h>

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
        else if (s[i] == 'C') { // 문자열에서 C일 경우 다음 문자가 M이나 D일 경우 100을 빼고, 그렇지 않은 경우 100을 더함
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
        else if (s[i] == 'X') { // 문자열에서 X일 경우 다음 문자가 C이나 L일 경우 10을 빼고, 그렇지 않은 경우 10을 더함
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
        else if (s[i] == 'I') { // 문자열에서 I일 경우 다음 문자가 X이나 V일 경우 1을 빼고, 그렇지 않은 경우 1을 더함
            if (i < len - 1 && (s[i + 1] == 'X' || s[i + 1] == 'V')) {
                result -= 1;
            }
            else {
                result += 1;
            }
        }
        else { // 올바르지 않은 입력인 경우 에러 메시지 출력 후 -1 반환
            cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
            return -1;
        }
    }

    return result;
}

int main() {
    string roman;
    int num;
    bool st = true;
    while (true) {
        roman = ""; //저장할 string 값을 초기화
        cout << "로마 숫자를 입력하세요. (esc를 누르면 종료): ";

        while (st) {
            while (!_kbhit()) { // 키보드 입력을 대기
            }
            char ch = _getch();  // 키보드 값을 받음
            if (ch == 27) {  // esc키일 경우 종료
                return 0;
            }
            else if (ch == 13) { // 엔터키일 경우 입력루프를 나가며 변환

                break;
            }
            else if (ch == 8) { // 백스페이스키일 경우 입력을지워줌
                cout << "\b";
                cout << " ";
                cout << "\b";
                roman.erase(roman.size() - 1);
            }
            else { // 그외 일 경우 입력된 키보드 값을 string에 저장
                cout << ch;
                roman = roman + ch;
            }
        }
        num = romanToInt(roman); // string 값을 변환

        if (num == -1) { // 잘못된 값일 경우 에러 메세지 출력
            continue;
        }
        cout << endl;
        if (num != 0) {
            cout << "변환된 숫자: " << num << endl;
        }
        else
        {
            cout << "값을 입력해주세요"<< endl;
        }
    }
    return 0;
}
