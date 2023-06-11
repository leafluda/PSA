#pragma once
#include "GameObjectUI.hpp"

using namespace std;

class Stage {
public:

    int StageArray[120];
    int StageLength = 0;
    Stage() {};

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
