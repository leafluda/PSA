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

class Scene; // 전방선언

// Object클래스
class Object {

public:

    int X;// 오브젝트의 좌측 상단 좌표
    int Y;// 오브젝트의 좌측 상단 좌표
    int DefaultX; // 초기 좌표 저장 변수
    int DefaultY; // 초기 좌표 저장 변수
    int Width; // 가로
    int Height; // 세로
    int speed; // 가속도

    bool Active;// 이 오브젝트가 그려지는지 안그려지는지

    // 오브젝트 이미지
    string** Image;

    Object() {}

    // 가로세로 값을 받아서 이미지 동적할당
    Object(int width, int height) {
        X = 0;
        Y = 0;
        Active = true;
        Width = width;
        Height = height;

        Image = new string * [Height];
        for (int i = 0; i < Height; i++) {
            Image[i] = new string[Width];
        }
    }

    // 소멸자에서 할당된 메모리 해제
    ~Object() {
        for (int i = 0; i < Height; i++) {
            delete[] Image[i];
        }
        delete[] Image;
    }

    virtual void Render(Scene& s) {} // Scene 객체를 매개변수로 받아서 ScreenBuffer에 다양한 Object를 렌더링하는 가상 함수

    virtual void ImagePaste() {} // 동적할당한 Image배열에 DefaultImage를 복사하는 가상 함수

    virtual void ResetPos() {} // 위치와 Active값을 초기 값으로 초기화

    virtual void SpeedUp(int GameSpeed) {}; // 가속도를 게임속도와 같게 업데이트
};
