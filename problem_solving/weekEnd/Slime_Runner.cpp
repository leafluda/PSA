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
    ios::sync_with_stdio(false); // 표준 입출력 가속화
    cin.tie(NULL);
    cout.tie(NULL);
    system("mode con cols=200 lines=41");

    GameEngine game;
    game.GameRun();

    return 0;
}
