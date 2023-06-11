#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>

// 텍스트와 배경 색상 정의
#define TextBlack "\033[30m"
#define TextRed "\033[31m"
#define TextGreen "\033[32m"
#define TextYellow "\033[33m"
#define TextBlue "\033[34m"
#define TextPink "\033[35m"
#define TextMint "\033[36m"
#define TextLgray "\033[37m"
#define TextGray "\033[90m"
#define TextLred "\033[91m"
#define TextLgreen "\033[92m"
#define TextLyellow "\033[93m"
#define TextLblue "\033[94m"
#define TextLpink "\033[95m"
#define TextLmint "\033[96m"
#define TextWhite "\033[97m"
#define BgBlack "\033[40m"
#define BgRed "\033[41m"
#define BgGreen "\033[42m"
#define BgYellow "\033[43m"
#define BgBlue "\033[44m"
#define BgPink "\033[45m"
#define BgMint "\033[46m"
#define BgLgray "\033[47m"
#define BgGray "\033[100m"
#define BgLred "\033[101m"
#define BgLgreen "\033[102m"
#define BgLyellow "\033[103m"
#define BgLblue "\033[104m"
#define BgLpink "\033[105m"
#define BgLmint "\033[106m"
#define BgWhite "\033[107m"
#define Reset "\033[0m"

// 텍스트와 배경 색상을 결합한 매크로 정의
#define Black TextBlack BgBlack
#define Red TextRed BgRed
#define Green TextGreen BgGreen
#define Yellow TextYellow BgYellow
#define Blue TextBlue BgBlue
#define Pink TextPink BgPink
#define Mint TextMint BgMint
#define Lgray TextLgray BgLgray
#define Gray TextGray BgGray
#define Lred TextLred BgLred
#define Lgreen TextLgreen BgLgreen
#define Lyellow TextLyellow BgLyellow
#define Lblue TextLblue BgLblue
#define Lpink TextLpink BgLpink
#define Lmint TextLmint BgLmint 
#define White TextWhite BgWhite
#define Text TextBlack BgWhite

using namespace std;

// 커서 위치 이동 함수
void GoToXY(int x, int y) {
    COORD Pos = { x,y };
    // 커서 위치 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = false; // 커서를 안보이게 설정
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

//템플릿을 사용하여 메모리 풀을 구현해 다양한 타입의 객체를 저장가능
template<class T>
class MemoryPool {

public:

    MemoryPool(int capacity) : capacity(capacity) {
        objects.reserve(capacity); // capacity만큼의 공간을 미리 예약한다.
        for (int i = 0; i < capacity; ++i) {
            objects.push_back(new T()); // T 타입의 객체를 생성하여 objects에 추가한다.
        }
    }

    ~MemoryPool() {
        for (T* object : objects) {
            delete object; // objects에 들어있는 모든 객체를 삭제한다.
        }
    }

    T* Acquire() {
        if (objects.empty()) { // objects가 비어있는 경우
            Expand(); // Expand 함수를 호출하여 capacity를 늘린다.
        }
        T* object = objects.back(); // objects의 마지막 요소를 가리키는 포인터를 가져온다.
        objects.pop_back(); // objects의 마지막 요소를 제거한다.
        return object; // 가져온 객체 포인터를 반환한다.
    }

    void Release(T* object) {
        objects.push_back(object); // objects에 객체 포인터를 추가한다.
    }

private:
    void Expand() {
        for (int i = 0; i < capacity; ++i) {
            objects.push_back(new T()); // T 타입의 객체를 생성하여 objects에 추가한다.
        }
        capacity *= 2; // capacity를 두 배로 늘린다.
    }

    vector<T*> objects; // T 타입의 객체 포인터를 저장하는 벡터
    int capacity; // 메모리 풀의 용량
};
