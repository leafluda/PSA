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

#define Reset "\033[0m"

using namespace std;

void GoToXY(int x, int y) { // 커서 위치 이동용

    COORD Pos = { x,y };
    //커서 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = false;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

template<class T>
class MemoryPool {
public:
    MemoryPool(int capacity) : capacity(capacity) {
        objects.reserve(capacity);
        for (int i = 0; i < capacity; ++i) {
            objects.push_back(new T());
        }
    }

    ~MemoryPool() {
        for (T* object : objects) {
            delete object;
        }
    }

    T* Acquire() {
        if (objects.empty()) {
            Expand();
        }
        T* object = objects.back();
        objects.pop_back();
        return object;
    }

    void Release(T* object) {
        objects.push_back(object);
    }

private:
    void Expand() {
        for (int i = 0; i < capacity; ++i) {
            objects.push_back(new T());
        }
        capacity *= 2;
    }

    vector<T*> objects;
    int capacity;
};
