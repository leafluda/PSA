#include <iostream>
#include <string>

using namespace std;

int main() {
    unsigned short num;
    string numStr;
    bool error = false;

    cout << "Enter a number: ";
    cin >> numStr;

    // Check if input is valid
    for (char c : numStr) {
        if (!isdigit(c)) {
            error = true;
            break;
        }
    }

    if (error || numStr.size() > 5) {
        cout << "Error: Invalid input" << endl;
        return 1;
    }

    num = stoi(numStr);

    if (num > USHRT_MAX) {
        cout << "Error: Input value is greater than the maximum value of unsigned short" << endl;
        return 1;
    }

    unsigned short reversedNum = 0;
    unsigned short tempNum = num;

    // Reverse the number
    while (tempNum > 0) {
        reversedNum = reversedNum * 10 + (tempNum % 10);
        tempNum /= 10;
    }

    if (reversedNum > USHRT_MAX) {
        cout << "Error: Reversed value is greater than the maximum value of unsigned short" << endl;
        return 1;
    }

    cout << "Reversed number: " << reversedNum << endl;
    return 0;
}
