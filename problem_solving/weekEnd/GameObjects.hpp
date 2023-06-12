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

// Cloud 클래스
class Cloud : public Object {

public:

    int MoveCount; // 구름의 이동에 사용되는 변수
    int MoveSpeed; // 구름의 이동 속도

    Cloud() {}

    Cloud(int x, int y, int width, int height, int cloudspeed) : Object(width, height) {
        X = x;
        Y = y;
        DefaultX = x;
        DefaultY = y;
        Width = width;
        Height = height;
        MoveSpeed = cloudspeed;
        Active = true;
        MoveCount = 0;
        ImagePaste();
    }

    // 구름의 기본 이미지
    string DefaultImage[7][15] = {
        {"  ","  ","  ","  ","  ","  ","■","■","  ","  ","  ","  ","  ","  ","  "},
        {"  ","  ","■","■","  ","■","■","■","■","  ","  ","▦","■","  ","  "},
        {"  ","■","■","■","■","■","■","■","■","  ","▦","■","■",White "■" Reset,"  "},
        {"  ","■","■","■","▦","■","■","■","■","▦","■","■","■","■",White "■" Reset},
        {"▦","▦","■","▦","▦","■","■","■","▦","▦","▦","■","■","■",Lgray"▦" Reset},
        {"▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦",Lgray "▦" Reset},
        {"  ","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦",Lgray"▦" Reset,"  "}
    };

    // 객체의 Active값을 설정하는 함수
    void setActive(bool b) {
        Active = b;
    }

    // 객체의 설정을 초기설정으로 바꾸는 함수
    void ResetPos() {
        X = DefaultX;
        Y = DefaultY;
        Active = true;
        MoveCount = 0;
    }

    // Scene 객체를 매개변수로 받아서 ScreenBuffer에 Object를 렌더링하는 함수
    void Render(Scene& s) {
        for (int i = 0; i < Height; i++) {
            if ((Y + i) < 39) {
                for (int j = 0; j < Width; j++) {
                    if (0 <= (X + j) && (X + j) < 100) {
                        if (Image[i][j] != "  ") {
                            s.ScreenBuffer[Y + i][X + j] = Image[i][j];
                        }
                    }
                }
            }
        }
    }

    // Object의 기본 이미지를 Image배열에 복사하는 함수
    void ImagePaste() {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 15; j++) {
                if (DefaultImage[i][j] == "■") {
                    if (j < 14 && DefaultImage[i][j + 1] == "  ") {
                        DefaultImage[i][j] = White"■" Reset;
                    } else {
                        DefaultImage[i][j] = White"■";
                    }
                } else if (DefaultImage[i][j] == "▦") {
                    if (j < 14 && DefaultImage[i][j + 1] == "  ") {
                        DefaultImage[i][j] = Lgray"▦" Reset;
                    } else {
                        DefaultImage[i][j] = Lgray"▦";
                    }
                }
                Image[i][j] = DefaultImage[i][j];
            }
        }
    }

    // 구름을 이동시키는 함수
    void MoveCloud() {
        if (MoveCount > 10) {
            X--;
            if (MoveCount > 15) {
                X--;
            }
            if (X + Width < 0) {
                X = 100;
            }
            MoveCount = 0;
        } else {
            MoveCount = MoveCount + speed + MoveSpeed;
        }
    }

    // 가속도를 게임속도와 같은속도로 업데이트 하는 함수
    void SpeedUp(int GameSpeed) {
        speed = GameSpeed;
    }
};

class Mountain : public Object {

public:

    int MoveCount; // 산의 이동에 사용되는 변수

    Mountain(int x, int y, int width, int height) : Object(width, height) {
        X = x;
        Y = y;
        DefaultX = x;
        DefaultY = y;
        Active = true;
        MoveCount = 0;
        Width = width;
        Height = height;
        ImagePaste();
    }

    // 산의 기본 이미지
    string DefaultImage[22][46] = {
        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","▣","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","▣","▣","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","▣","▣","▧","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","▣","▧","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","▣","▣","▧","  ","  ","  ","▣","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","▣","▣","▣","▧","▧","  ","■","■","▣","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","■","▣","▣","▣","▣","▧","■","■","■","▣","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","▣","▣","▣","▣","▣","▧","▧","■","■","▣","▣","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","■","▣","▣","▣","▣","▣","▣","▧","▧","▣","▣","▣","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","■","▣","▣","▣","▣","▣","▣","▣","▧","▧","▧","▣","▣","▧","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","■","■","▣","▣","▣","■","▣","▣","▣","▣","▧","▧","▧","▧","▣","▧","  ","  ","  ","  ","  ","  ","■","  ","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","■","■","■","▣","▣","▣","■","▣","▣","▣","▣","▣","▧","▧","▧","▧","▧","▧","  ","  ","  ","  ","■","■","▣","  ","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","■","■","▣","▣","▣","■","▣","▣","▣","▣","▣","▣","▧","▧","▧","▧","▧","▧","▧","  ","  ","■","■","▣","▣","▣","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","■","■","▣","▣","■","▣","▣","▣","▣","▣","▣","▣","▣","▧","▧","▧","▧","▧","▧","▧","■","■","■","▣","▣","▣","  ","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","■","■","▣","▣","■","■","▣","▣","▣","▣","▣","▧","▣","▣","▣","▧","▧","▧","▧","■","■","■","■","▣","▣","▣","▧","▧","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","■","■","■","▣","▣","■","■","▣","▣","▧","▣","▣","▧","▧","▣","▣","▣","▧","▧","▧","■","■","■","■","▣","▣","▣","▧","▧","  ","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","■","■","■","▣","■","▣","▣","■","■","■","▣","▣","▧","▧","▣","▣","▧","▧","▧","▣","▧","▧","■","■","■","■","■","▣","▣","▣","▧","▧","▧","  ","  ","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","  ","■","■","▣","■","▣","▣","■","■","■","■","▣","▣","▣","▧","▧","▣","▧","▧","▧","▧","▧","■","■","▣","▣","■","▣","▣","▣","▧","▧","▧","▧","▧","▧","  ","  ","  "},

        {"  ","  ","  ","  ","  ","  ","  ","■","■","▣","■","▣","▣","■","■","■","■","▣","▣","▣","▣","▧","▧","▧","▧","▧","▧","▧","■","■","▧","▣","▣","■","▣","▣","▣","▧","▧","▧","▧","▧","▧","▧","  ","  "},

        {"  ","  ","  ","  ","  ","  ","■","▣","▣","▧","■","■","■","■","■","■","■","▣","▣","▣","▣","▣","▧","▧","▧","▧","▧","■","▧","▧","▧","▣","■","▣","▣","▣","▧","▧","▧","▧","▣","▧","▧","▧","▧","  "},

        {"  ","  ","  ","  ","■","■","▣","▣","▧","▧","▣","■","■","■","■","■","▣","▣","▣","▣","▣","▣","▧","▧","▧","▧","■","▧","▧","▧","▣","▣","▣","▣","▣","▧","▧","▧","▣","▧","▣","▣","▧","▧","▧","  "},

        {"■","■","■","■","▣","▣","▣","▧","▧","▧","▣","▣","■","■","■","▣","▣","▣","▣","▣","▣","▧","▧","▧","▧","▧","▧","▧","▧","▣","▣","▣","▣","▣","▧","▧","▧","▣","▣","▧","▣","▣","▣","▧","▧","  "}
    };

    // 객체의 Active값을 설정하는 함수
    void setActive(bool b) {
        Active = b;
    }

    // 객체의 설정을 초기설정으로 바꾸는 함수
    void ResetPos() {
        X = DefaultX;
        Y = DefaultY;
        Active = true;
        MoveCount = 0;
    }

    // Scene 객체를 매개변수로 받아서 ScreenBuffer에 Object를 렌더링하는 함수
    void Render(Scene& s) {
        for (int i = 0; i < Height; i++) {
            if ((Y + i) < 39) {
                for (int j = 0; j < Width; j++) {
                    if (0 <= (X + j) && (X + j) < 100 && Image[i][j] != "  ") {
                        s.ScreenBuffer[Y + i][X + j] = Image[i][j];
                    }
                }
            }
        }
    }

    // Object의 기본 이미지를 Image배열에 복사하는 함수
    void ImagePaste() {
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 46; j++) {
                if (DefaultImage[i][j] == "■") {
                    if (j < 45 && DefaultImage[i][j + 1] == "  ") {
                        DefaultImage[i][j] = White"■" Reset;
                    } else {
                        DefaultImage[i][j] = White"■";
                    }
                } else if (DefaultImage[i][j] == "▣") {
                    if (j < 45 && DefaultImage[i][j + 1] == "  ") {
                        DefaultImage[i][j] = Lgray"▣" Reset;
                    } else {
                        DefaultImage[i][j] = Lgray"▣";
                    }
                } else if (DefaultImage[i][j] == "▧") {
                    if (j < 45 && DefaultImage[i][j + 1] == "  ") {
                        DefaultImage[i][j] = Gray"▧" Reset;
                    } else {
                        DefaultImage[i][j] = Gray"▧";
                    }
                }
                Image[i][j] = DefaultImage[i][j];
            }
        }
    }

    // 산을 이동시키는 함수
    void MoveMountain() {
        if (MoveCount > 50) {
            X--;
            if (X + Width < 0) {
                X = 100;
            }
            MoveCount = 0;
        } else {
            MoveCount = MoveCount + speed + 1; // 가속도 만큼 더해서 MoveCount를 더함
        }
    }

    // 가속도를 게임속도와 같은속도로 업데이트 하는 함수
    void SpeedUp(int GameSpeed) {
        speed = GameSpeed;
    }
};

// Ground 클래스
class Ground : public Object {

public:

    int FlowerCount; // 땅의 이미지를 다양하게 하기위해 사용된 변수

    Ground(int width, int height) : Object(width, height) {
        X = 0;
        Y = 35;
        DefaultX = 0;
        DefaultY = 35;
        Active = true;
        FlowerCount = 0;
        Width = width;
        Height = height;
        SetImage();
    }

    // 땅의 움직임을 구현하기 위해 사용된 변수
    string tempImage[4][100];

    // 땅의 이미지를 Image에 그리는 함수
    void SetImage() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 100; j++) {
                if ((FlowerCount + i) == 8) {
                    Image[i][j] = Lgreen"■";
                    FlowerCount = 0;
                }
                else {
                    Image[i][j] = Green"■";
                    FlowerCount++;
                }
            }
        }
    }

    // 객체의 Active값을 설정하는 함수
    void setActive(bool b) {
        Active = b;
    }

    // 객체의 설정을 초기설정으로 바꾸는 함수
    void ResetPos() {
        X = DefaultX;
        Y = DefaultY;
        Active = true;
        FlowerCount = 0;
    }

    // Scene 객체를 매개변수로 받아서 ScreenBuffer에 Object를 렌더링하는 함수
    void Render(Scene& s) {
        for (int i = 0; i < Height; i++) {
            if ((Y + i) < 39) {
                for (int j = 0; j < Width; j++) {
                    if (0 <= (X + j) && (X + j) < 100) {
                        if (Image[i][j] != "  ") {
                            s.ScreenBuffer[Y + i][X + j] = Image[i][j];
                        }
                    }
                }
            }
        }
    }

    // 땅을 이동시키는 함수
    void MoveGround() {
            for (int i = 0; i < Height; i++) {
                for (int j = 0; j < Width; j++) {
                    tempImage[i][j] = Image[i][j];
                }
            }
            for (int i = 0; i < Height; i++) {
                for (int j = 0; j < (Width - 1); j++) {
                    Image[i][j] = tempImage[i][j + 1];
                }
                Image[i][99] = tempImage[i][0];
            }
    }
};

// Sword 클래스
class Sword : public Object {

public:

    bool IsFalling; // 검이 떨어지고 있는지 체크하는 변수
    bool DefaultType; // 초기 형태가 검이 떨어지는 검인지 박혀있는 검인지 저장하는 변수

    Sword() {}

    Sword(int x, int y, int width, int height, bool isfalling) : Object(width, height) {
        X = x;
        Y = y;
        DefaultX = x;
        DefaultY = y;
        Active = true;
        Width = width;
        Height = height;
        IsFalling = isfalling;
        DefaultType = isfalling;
        ImagePaste();
    }

    // 검의 기본 이미지
    string DefaultImage[12][1] = {
                    {Red"■" Reset},
        {BgRed TextWhite"◆" Reset},
        {BgRed TextWhite"◆" Reset},
        {BgRed TextWhite"◆" Reset},
                 {Yellow"  " Reset},
                  {White"  " Reset},
                  {White"  " Reset},
                  {White"  " Reset},
                  {White"  " Reset},
                  {White"  " Reset},
                  {White"  " Reset},
                  {White"  " Reset}
    };

    // Object의 기본 이미지를 Image배열에 복사하는 함수
    void ImagePaste() {
        for (int i = 0; i < 12; i++) {
            Image[i][0] = DefaultImage[i][0];
        }
    }

    // Scene 객체를 매개변수로 받아서 ScreenBuffer에 Object를 렌더링하는 함수
    void Render(Scene& s) {
        for (int i = 0; i < Height; i++) {
            if ((Y + i) < 39) {
                for (int j = 0; j < Width; j++) {
                    if (0 <= (X + j) && (X + j) < 100) {
                        if (Image[i][j] != "  ") {
                            s.ScreenBuffer[Y + i][X + j] = Image[i][j];
                        }
                    }
                }
            }
        }
    }

    // 객체의 설정을 초기설정으로 바꾸는 함수
    void ResetPos() {
        X = DefaultX;
        Y = DefaultY;
        Active = false;
        IsFalling = DefaultType;
    }

    // 객체의 Active값을 설정하는 함수
    void setActive(bool b) {
        Active = b;
    }

    // 검을 이동시키는 함수
    void MoveSword() {
        if (IsFalling == false) {
            for (int s = -1; s < speed; s++) { // 가속도 만큼 더 이동
                X--;
                if (X + Width < 0) {
                    ResetPos();
                    break;
                }
            }                 
        }
    }

    // 검을 떨어뜨리는 함수
    void FallingSword() {
        if (IsFalling == true) {
            for (int s = -1; s < speed; s++) { // 가속도 만큼 더 빠르게 떨어짐 
                Y++;
                if (Y > 26) {
                    IsFalling = false;
                    break;
                }
            }
        }
    }

    // 가속도를 게임속도와 같은속도로 업데이트 하는 함수
    void SpeedUp(int GameSpeed) {
        speed = GameSpeed;
    }
};

// Player 클래스
class Player : public Object {

public:

    int MoveCount; // 플레이어의 전진 모션에 사용되는 변수
    int JumpCount; // 점프하는 시간을 체크하는 변수

    bool IsJump; // 플레이어가 점프하는중인지 확인하는 변수
    bool IsFalling; // 플레이어가 떨어지고 있는 중인지 확인하는 변수

    Player(int x, int y, int width, int height) : Object(width, height) {
        X = x;
        Y = y;
        DefaultY = y;
        Active = true;
        MoveCount = 0;
        JumpCount = 0;
        IsFalling = false;
        IsJump = false;
        Width = width;
        Height = height;
        ImagePaste();
    }

    // 플레이어의 기본 이미지
    string DefaultImage[10][10] = {
        {"  ","  ","  ","  ","■","  ","  ","  ","  ","  "},

        {"  ","  ","  ","■","■","■","  ","  ","  ","  "},

        {"  ","  ","■","■","■","■","□","  ","  ","  "},

        {"  ","▤","▤","■","■","■","□","□","  ","  "},

        {"■","▤","▤","■","■","■","■","■","□","  "},

        {"■","■","■","▣","■","■","■","▣","□","▧"},

        {"■","■","■","■","■","▲","■","■","□","▧"},

        {"■","■","■","■","■","■","■","□","▧","▤"},

        {"  ","■","■","■","□","□","□","▧","▤" ,"  "},

        {"  ","  ","□","□","▧","▧","▧" ,"  ","  ","  "}
    };

    // Scene 객체를 매개변수로 받아서 ScreenBuffer에 Object를 렌더링하는 함수
    void Render(Scene& s) {
        for (int i = 0; i < Height; i++) {
            for (int j = 0; j < Width; j++) {
                if (Image[i][j] != "  ") {
                    s.ScreenBuffer[Y + i][X + j] = Image[i][j];
                }
            }
        }
    }

    // 객체의 설정을 초기설정으로 바꾸는 함수
    void ResetPos() {
        Active = true;
        MoveCount = 0;
        JumpCount = 0;
        IsFalling = false;
        IsJump = false;
        Y = DefaultY;
    }

    // 객체의 기본 이미지를 Image에 복사하는 함수
    void ImagePaste() {
        for (int i = 0; i < Height; i++) {
            for (int j = 0; j < Width; j++) {
                Image[i][j] = DefaultImage[i][j];
            }
        }

        for (int i = 0; i < Height; i++) {
            for (int j = 0; j < Width; j++) {
                if (DefaultImage[i][j] == "■") {
                    DefaultImage[i][j] = Lmint"■" Reset;
                } else if (DefaultImage[i][j] == "▤") {
                    DefaultImage[i][j] = White"▤" Reset;
                } else if (DefaultImage[i][j] == "□") {
                    DefaultImage[i][j] = Mint"□" Reset;
                } else if (DefaultImage[i][j] == "▧") {
                    DefaultImage[i][j] = Lblue"▧" Reset;
                } else if (DefaultImage[i][j] == "▲" || DefaultImage[i][j] == "▣") {
                    DefaultImage[i][j] = TextBlack BgLmint + DefaultImage[i][j];
                }
                Image[i][j] = DefaultImage[i][j];
            }
        }
    }

    // 플레이어의 이동 모션을 보여주는 함수
    void MovePlayer() {
        if (IsJump == false) {
            if (MoveCount < 4) {
                Y--;
                MoveCount++;
            } else {
                Y++;
                MoveCount++;
                if (MoveCount >= 8) {
                    MoveCount = 0;
                }
            }
        } else {
            MoveCount = 0;
        }
    }

    // 플레이어의 점프 기능을 구현하는 함수
    void JumpPlayer() {
        if (IsJump == true) {
            if (IsFalling == false) {                    
                Y--;
                JumpCount++;
                if (JumpCount >= 15) {
                    IsFalling = true;
                }                    
            } else if (IsFalling == true) {
                Y++;
                JumpCount--;
                if (JumpCount <= 1) {
                    IsFalling = false;
                    IsJump = false;
                    Y = DefaultY;
                }
            }
        }
    }
};
