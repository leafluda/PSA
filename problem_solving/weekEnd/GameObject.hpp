#pragma once
#include "Utility.hpp"
using namespace std;

class Scene;

class Object {

public:

    int X;//오브젝트의 좌측 상단 좌표
    int Y;
    int DefaultX;
    int DefaultY;
    int Width; //가로
    int Height; //세로
    int speed;
    bool Active;//이 오브젝트가 그려지는지 안그려지는지

    //오브젝트 이미지
    string** Image;

    Object() {}

    //가로세로 값을 받아서 이미지 동적할당
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

    //소멸자에서 할당된 메모리 해제
    ~Object() {
        for (int i = 0; i < Height; i++) {
            delete[] Image[i];
        }
        delete[] Image;
    }

    virtual void Render(Scene& s) {}

    virtual void ImagePaste() {}

    virtual void ResetPos() {}

    virtual void SpeedUp(int GameSpeed) {};
};
