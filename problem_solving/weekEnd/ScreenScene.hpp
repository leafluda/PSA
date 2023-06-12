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

// Scene 클래스
class Scene {

public:

    string Output; // 출력용
    string ScreenBuffer[39][100]; // x 100, y 40
    vector<Object*> Objects; // Scene이 가지고 있는 Object의 리스트
    int bgtrue;
    Scene() {
        Output = "";
        ClearScreenBuf();
        bgtrue = true;
    }

    // Active한 Object의 Render를 호출해 ScreenBuffer에 저장하고 ScreenBuffer 출력
    void Draw() {
        bgtrue = true;
        for (Object* obj : Objects) {
            if (obj->Active == true) {
                obj->Render(*this);
            }
        }
        Output = "";
        for (int i = 0; i < 39; i++) {
            for (int j = 0; j < 100; j++) {
                if(ScreenBuffer[i][j] == "  " && bgtrue == true){
                    ScreenBuffer[i][j] = Lmint"  ";
                    bgtrue = false;
                } else if (ScreenBuffer[i][j] != "  ") {
                    bgtrue = true;
                }
                Output += ScreenBuffer[i][j];
            }
            Output += Reset"\n";
            bgtrue = true;
        }
        cout << Output;
        cout.flush();
    }

    // ScreenBuffer에 저장된 Object를 지워 ScreenBuffer를 초기화
    void ClearScreenBuf() {
        for (int i = 0; i < 39; i++) {
            for (int j = 0; j < 100; j++) {
                ScreenBuffer[i][j] = "  ";
            }
        }
    }

        // Objects에 저장된 Object들을 초기 위치, 설정으로 되돌림
    void ResetObject() {
        for (Object* obj : Objects) {
            if (obj->Active == true) {
                obj->ResetPos();
            }
        }
    }

    // Object의 가속도를 게임속도로 업데이트 시킴
    void SpeedObject(int GameSpeed) {
        for (Object* obj : Objects) {
            if (obj->Active == true) {
                obj->SpeedUp(GameSpeed);
            }
        }
    }

    //object벡터에 오브젝트추가하는 함수
    void InsertObject(Object& o) {
        Objects.insert(Objects.begin()+1,&o);
    }

    void AddObject(Object& o) {
        Objects.push_back(& o);
    }
};
