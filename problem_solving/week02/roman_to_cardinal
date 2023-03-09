#include <iostream>
#include <string>

using namespace std;

string toRoman(int num);

int main() {
    int num;
    string roman;

    while (true) {
        cout << "1 ~ 3999 사이의 숫자를 입력해 주세요.(0 입력시 종료): ";
        string input;
        cin >> input;

        if (input == "0") {
            break;
        }

        if (input.length() == 0 || !isdigit(input[0])) {
            cout << "Error: 잘못된 입력입니다. 1 ~ 3999 사이의 숫자를 입력해 주세요." << endl;
            continue;
        }

        num = stoi(input);

        if (num < 1 || num > 3999) {
            cout << "Error: 1 ~ 3999 사이의 숫자를 입력해 주세요." << endl;
            continue;
        }

        roman = toRoman(num);
        cout << num << " ==로마자 변환=> " << roman << endl;
    }

    return 0;
}

string toRoman(int num) {
    string roman;

    const string romanNumerals[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
    const int decimalValues[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };

    for (int i = 0; i < 13; i++) {
        while (num >= decimalValues[i]) {
            roman += romanNumerals[i];
            num -= decimalValues[i];
        }
    }

    return roman;
}
