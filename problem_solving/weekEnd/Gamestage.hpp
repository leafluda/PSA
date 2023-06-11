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

using namespace std;

// Stage 클래스
class Stage {

public:

    int StageArray[120]; // Stage를 저장할 배열
    int StageLength = 0; // 스테이지의 길이를 저장하는 배열

    Stage() {};

    // 파일에서 스테이지의 정보를 배열에 저장하는 함수
    void readDataFromFile(const string& filename) {
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cout << "파일 열기 실패" << "\n";
            return;
        }

        string line;
        int row = 0;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string token;
            int col = 0;
            while (getline(iss, token, ',')) {
                StageArray[col] = stoi(token);
                col++;
            }
            StageLength = col;
        }
        inputFile.close();
    }
};
