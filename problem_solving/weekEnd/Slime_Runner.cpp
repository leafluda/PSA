#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include "GameEngine.hpp"

using namespace std;

int main() {
    // 표준 입출력 가속화
    ios::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);

    // 콘솔창 크기 설정
    system("mode con cols=200 lines=41");

    // 게임 엔진 객체 생성
    GameEngine game;
    // 게임 시작
    game.GameRun();

    return 0;
}
