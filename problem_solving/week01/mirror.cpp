#include <iostream>
#include <limits>
#include <conio.h>
using namespace std;

// 입력 받은 숫자를 뒤집는 함수
unsigned short reverse_number(unsigned short num) {
    unsigned short rev = 0;
    while (num > 0) {
        rev = rev * 10 + num % 10;
        num /= 10;
    }
    return rev;
}

int main() {
    unsigned short num;
    char input;
    bool esc = true;

    while (esc)
    {
        cout << "숫자를 입력하세요: ";
        if (cin >> num) {
            // 입력한 값이 unsigned short 범위 내에 있는지 확인
            if (num > numeric_limits<unsigned short>::max()) {
                cout << "에러: 입력값이 unsigned short 범위를 초과했습니다." << endl;
                cin.clear();  // 오류 플래그 초기화
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 비우기
            }
            else {
                unsigned short rev_num = reverse_number(num);
                // 결과값이 unsigned short 범위 내에 있는지 확인
                if (rev_num > numeric_limits<unsigned short>::max()) {
                    cout << "에러: 결과값이 unsigned short 범위를 초과했습니다." << endl;
                }
                else {
                    cout << "입력한 숫자의 역순은 " << rev_num << " 입니다." << endl;
                    cout << "다시 숫자를 입력하시겠습니까? (esc를 누르면 종료, 그외의 키를 입력하면 계속): ";
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
            }
        }
        else {
            cout << "에러: 올바른 숫자가 아닙니다." << endl;
            cin.clear();  // 오류 플래그 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 비우기
        }
    }

    return 0;
}
