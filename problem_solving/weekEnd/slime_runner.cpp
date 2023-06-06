#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include "Colors.hpp"
#include <variant>

using namespace std;

class Utility {

public:
    Utility() {}

    void gotoxy(int x, int y) { // 커서 위치 이동용

        COORD Pos = { x,y };
        //커서 이동
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

        CONSOLE_CURSOR_INFO ConsoleCursor;
        ConsoleCursor.bVisible = false;
        ConsoleCursor.dwSize = 1;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
    }
};

class Scene;

class Object {

public:

    //오브젝트의 좌측 상단 좌표
    int X;
    int Y;

    int Width; //가로
    int Height; //세로

    //이 오브젝트가 그려지는지 안그려지는지
    bool Active;

    //오브젝트 이미지
    string** image;

    //가로세로 값을 받아서 이미지 동적할당
    Object(int width, int height) {
        X = 0;
        Y = 0;
        Active = true;
        Width = width;
        Height = height;

        image = new string * [Height];
        for (int i = 0; i < Height; i++)
        {
            image[i] = new string[Width];
        }
    }

    //소멸자에서 할당된 메모리 해제
    ~Object() {
        for (int i = 0; i < Height; i++) {
            delete[] image[i];
        }
        delete[] image;
    }

    virtual void Render(Scene& s) {}

    virtual void ImagePaste() {}
};

class Scene {

public:

    ostringstream output; // 출력용
    string ScreenBuffer[39][100]; // x 100, y 40
    vector<Object*> objects;
    Utility u;


    Scene() {
        ClearScreenBuf();
    }

    // Active한 Object의 Render를 호출해 ScreenBuffer에 저장하고 ScreenBuffer 출력
    void Draw(int score, int speed) {
        for (Object* obj : objects) {
            obj->Render(*this);
        }
        output.str("");
        for (int i = 0; i < 39; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                output << ScreenBuffer[i][j];
            }
            output << Reset"\n";
        }
        cout << output.str();
        cout << "점수 : " << score << " , 속도 : " << speed;
        cout.flush();
    }

    // ScreenBuffer에 저장된 Object를 지워 ScreenBuffer를 초기화
    void ClearScreenBuf() {
        for (int i = 0; i < 39; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                ScreenBuffer[i][j] = "  ";
            }
        }
    }

    //object벡터에 오브젝트추가하는 함수
    void AddObject(Object& o) {
        objects.push_back(&o);
    }
};

// 플레이어 모양을 저장하고 플레이어가 사용할 함수 선언
class Player : public Object
{

public:
    Utility u;
    int MoveCount;
    bool IsJump;
    bool IsFalling;
    int JumpCount;
    int ObjectYDefault;

    Player(int x, int y, int width, int height) : Object(width, height) {
        X = x;
        Y = y;
        ObjectYDefault = y;
        Active = true;
        MoveCount = 0;
        JumpCount = 0;
        IsFalling = false;
        IsJump = false;
        Width = width;
        Height = height;
        ImagePaste();
    }
    
    string defaultimage[10][10] = {
        {"  ","  ","  ","  ",Lmint"■" Reset,"  ","  ","  ","  ","  "},
        {"  ","  ","  ",Lmint"■",Lmint"■" Reset,"  ","  ","  ","  ","  "},
        {"  ","  ",Lmint"■",Lmint"■",Lmint"■",Lmint"■" Reset,"  ","  ","  ","  "},
        {"  ",White"■",White"■",Lmint"■",Lmint"■",Lmint"■",Mint"■",Mint"■" Reset,"  ","  "},
        {Lmint"■",White"■",White"■",Lmint"■",Lmint"■",Lmint"■",Lmint"■",Mint"■",Mint"■" Reset,"  "},
        {Lmint"■",Lmint"■",Lmint"■",TextWhite BgBlack"▣",Lmint"■",Lmint"■",Lmint"■",TextWhite BgBlack"▣",Mint"■",Lblue"■" Reset},
        {Lmint"■",White"■",Lmint"■",Lmint"■",Lmint"■",TextBlack BgLmint"▲",Lmint"■",Lmint"■",Mint"■",Lblue"■" Reset},
        {Lmint"■",Lmint"■",Lmint"■",Lmint"■",Lmint"■",Lmint"■",Lmint"■",Mint"■",Lblue"■",White"■" Reset},
        {"  ",Lmint"■",Lmint"■",Lmint"■",Mint"■",Mint"■",Mint"■",Lblue"■",White"■" Reset,"  "},
        {"  ","  ",Mint"■",Mint"■",Lblue"■",Lblue"■",Lblue"■" Reset,"  ","  ","  "}
    };

    void Render(Scene& s) {
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                if (image[i][j] != "  ")
                {
                    s.ScreenBuffer[Y + i][X + j] = image[i][j];
                }
            }
        }
    }

    void ImagePaste() {
        for (int i = 0; i < Height; i++) {
            for (int j = 0; j < Width; j++) {
                image[i][j] = defaultimage[i][j];
            }
        }
    }

    void MovePlayer() {
        if (IsJump == false) {
            if (MoveCount < 2) {
                Y++;
                MoveCount++;
            }
            else {
                Y--;
                MoveCount++;
                if (MoveCount >= 4)
                {
                    MoveCount = 0;
                }
            }
        }
        else {
            MoveCount = 0;
        }
    }

    void JumpPlayer() {
        if (IsJump == true) {
            if (IsFalling == false) {
                Y--;
                JumpCount++;
                if (JumpCount >= 15)
                {
                    IsFalling = true;
                }
            }
            else if (IsFalling == true) {
                Y++;
                JumpCount--;
                if (JumpCount <= 1)
                {
                    IsFalling = false;
                    IsJump = false;
                    Y = ObjectYDefault;
                }
            }
        }
    }
};

class Cloud : public Object
{
public:
    Utility u;
    int MoveCount;
    int MoveSpeed;

    Cloud(int x, int y, int width, int height, int speed) : Object(width, height) {
        X = x;
        Y = y;
        Active = true;
        MoveCount = 0;
        Width = width;
        Height = height;
        MoveSpeed = speed;
        ImagePaste();
    }

    string defaultimage[8][15] = {
        {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  " , "  ", "  ", "  ", "  ", "  ", "  "},
        {"  ", "  ", "  ", "  ", "  ", "  ", White"■", White"■" Reset, "  " , "  ", "  ", "  ", "  ", "  ", "  "},
        {"  ", "  ", White"■", White"■" Reset, "  ", White"■", White"■", White"■", White"■" Reset, "  ", "  ", Lgray"■", White"■" Reset, "  ", "  "},
        {"  ", White"■", White"■", White"■", White"■", White"■", White"■", White"■", White"■" Reset, "  ", Lgray"■", White"■", White"■", White"■" Reset, "  "},
        {"  ", White"■", White"■", White"■", Lgray"■", White"■", White"▦", White"■", White"■" , Lgray"■", White"■", White"■", White"■", White"■", White"■" Reset},
        {Lgray"■", Lgray"■", White"■", Lgray"■", Lgray"■", White"■", White"■", White"■", Lgray"■", Lgray"■", Lgray"■", White"■", White"■", White"■", Lgray"■" Reset},
        {Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■" Reset},
        {"  ", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■", Lgray"■",Lgray"■", Lgray"■", Lgray"■" Reset, "  "}
    };

    void setActive(bool b) {
        Active = b;
    }

    void Render(Scene& s) {
        for (int i = 0; i < Height; i++)
        {
            if ((Y + i) < 39)
            {
                for (int j = 0; j < Width; j++)
                {
                    if (0 <= (X + j) && (X + j) < 100)
                    {   
                        if (image[i][j] != "  ")
                        {
                            s.ScreenBuffer[Y + i][X + j] = image[i][j];
                        }
                    }
                }
            }
        }
    }

    void ImagePaste() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 15; j++) {
                image[i][j] = defaultimage[i][j];
            }
        }
    }

    void MoveCloud() {
            if (MoveCount == MoveSpeed) {
                X--;
                if (X + Width < 0) {
                    X = 100;
                }
                MoveCount = 0;
            }
            else {
                MoveCount++;
            }
    }
};

class Mountain : public Object
{
public:
    Utility u;
    int MoveCount;
    int MoveSpeed;

    Mountain(int x, int y, int width, int height) : Object(width, height) {
        X = x;
        Y = y;
        Active = true;
        MoveCount = 0;
        Width = width;
        Height = height;
        MoveSpeed = 100;
        ImagePaste();
    }

    string defaultimage[22][55] = {

        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"▣" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"■",White"▣",Lgray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"■",White"■",White"▣",Lgray"■",Lgray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
        {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
                  {"  ","  ","  ","  ",White"▦" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
                  {"  ","  ","  ","  ",White"■",Lgray"▦",Lgray"▦" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
                  {"  ","  ","  ","  ",White"■",Lgray"▦",Lgray"■",Lgray"▦",Lgray"▦" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
                       {"  ","  ","  ",White"■",Lgray"■",Lgray"■",Lgray"▦",Lgray"■",Lgray"■",Lgray"▦",Lgray"▦" Reset,"  ","  ","  ","  ","  ","  ",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"□" Reset,"  ","  "},
                       {"  ","  ","  ",White"■",White"■",Lgray"■",Lgray"■",Lgray"▦",Lgray"■",Lgray"■",Lgray"■",Lgray"▦",Lgray"▦" Reset,"  ","  ","  ",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"□",Lgray"■" Reset,"  ","  "},
                       {"  ","  ","  ",White"■",White"■",White"■",Lgray"■",Lgray"■",Lgray"▦",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"▦",White"▦",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ",White"□",Lgray"■",Lgray"■" Reset,"  ","  "},
                  {"  ","  ",White"■",Lgray"■",White"■",White"■",White"■",Lgray"■",Lgray"■",Lgray"▦",Lgray"▦",Lgray"▦",Lgray"■",Lgray"■",White"■",White"▦",White"▦",White"■",White"■",Lgray"■",Gray"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Lgray"■",Gray"■",Gray"■",Gray"■" Reset,"  ","  ","  ","  ","  ","  ","  ","  ",White"□",Lgray"■",Lgray"■",Lgray"■" Reset,"  ","  "},
                  {"  ","  ",White"■",Lgray"■",White"■",White"■",White"■",White"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"▦",White"■",White"■",White"■",White"■",White"▦",White"▦",Lgray"■",Gray"■",Gray"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■" Reset,"  ","  ","  ","  ","  ","  ",White"□",White"■",Lgray"■",Lgray"■",Lgray"■" Reset,"  ","  "},
                  {"  ","  ",White"■",Lgray"■",Lgray"■",White"■",White"■",White"■",White"■",Lgray"■",Lgray"■",Lgray"■",Lgray"▦",Gray"■",White"■",White"■",White"■",White"■",Lgray"■",Lgray"▦",Lgray"▦",Gray"■",Gray"■",Gray"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▣",Lgray"■",Lgray"■",Gray"■",Gray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■" Reset,"  ","  ","  ","  ",White"□",White"■",White"■",Lgray"■",Lgray"■",Lgray"■" Reset,"  ","  "},
             {"  ",White"■",White"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",White"■",Lgray"■",Lgray"■",Lgray"▦",Gray"■",Gray"■",White"■",White"■",White"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"▦",Gray"▦",Gray"■",Gray"■",Gray"■",White"■",White"■",White"■",White"■",White"■",Lgray"▣",Gray"■",Gray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■" Reset,"  ","  ",White"□",White"■",White"■",White"■",White"■",White"■",Lgray"■",Lgray"■" Reset,"  "},
             {"  ",White"■",White"■",White"■",Lgray"■",Lgray"■",Lgray"■",White"■",White"■",White"■",Lgray"▦",Gray"■",Gray"■",Gray"■",Gray"■",White"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"▦",Gray"▦",Gray"■",Gray"■",White"■",White"■",White"■",White"■",Gray"▣",Gray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",White"□",White"■",White"■",White"■",White"■",White"■",White"■",White"■",Gray"■" Reset,"  "},
             {"  ",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▦",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"▦",Gray"▦",Gray"■",White"■",White"■",White"▣",Gray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",White"□",White"■",White"■",White"■",White"■",White"■",White"■",Gray"■",Gray"■",Gray"■" Reset,"  "},
        {White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"▦",Gray"▦",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"▦",Gray"▦",White"▣",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",White"□",White"■",White"■",White"■",White"■",White"■",White"■",White"■",Gray"■",Gray"■",Gray"■" Reset,"  "},
        {White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",Gray"▦",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"▦",Lgray"▦",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",White"□",White"■",White"■",White"■",White"■",White"■",White"■",White"■",Gray"■",Gray"■",Gray"■",Gray"■" Reset,"  "},
        {White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",White"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Lgray"▦",Lgray"▦",Lgray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",White"□",White"■",White"■",White"■",White"■",White"■",White"■",White"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■",Gray"■" Reset}
    };

    void setActive(bool b) {
        Active = b;
    }

    void Render(Scene& s) {
        for (int i = 0; i < Height; i++)
        {
            if ((Y + i) < 39)
            {
                for (int j = 0; j < Width; j++)
                {
                    if (0 <= (X + j) && (X + j) < 100)
                    {
                        if (image[i][j] != "  ")
                        {
                            s.ScreenBuffer[Y + i][X + j] = image[i][j];
                        }
                    }
                }
            }
        }
    }

    void ImagePaste() {
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 55; j++) {
                image[i][j] = defaultimage[i][j];
            }
        }
    }

    void MoveMountain() {
            if (MoveCount == MoveSpeed) {
                X--;
                if (X + Width < 0) {
                    X = 100;
                }
                MoveCount = 0;
            }
            else {
                MoveCount++;
            }
    }
};

class Ground : public Object
{

public:
    Utility u;
    int FlowerCount;

    Ground(int width, int height ): Object(width, height) {
        X = 0;
        Y = 35;
        Active = true;
        FlowerCount = 0;
        Width = width;
        Height = height;
        SetImage();
    }

    string tempImage[4][100];

    void SetImage()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if ((FlowerCount + i)== 8) {
                    image[i][j] = Lgreen"■";
                    FlowerCount = 0;
                }
                else {
                    image[i][j] = Green"■";
                    FlowerCount++;
                }
            }
        }
    }

    void setActive(bool b) {
        Active = b;
    }

    void Render(Scene& s) {
        for (int i = 0; i < Height; i++)
        {
            if ((Y + i) < 39)
            {
                for (int j = 0; j < Width; j++)
                {
                    if (0 <= (X + j) && (X + j) < 100)
                    {
                        if (image[i][j] != "  ")
                        {
                            s.ScreenBuffer[Y + i][X + j] = image[i][j];
                        }
                    }
                }
            }
        }
    }

    void MoveGround() {
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                tempImage[i][j] = image[i][j];
            }
        }
        
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < (Width-1); j++)
            {   
                image[i][j] = tempImage[i][j + 1];
            }
        }

        for (int i = 0; i < Height; i++)
        {
            image[i][99] = tempImage[i][0];
        }
    } 
};

class Sword : public Object {
public :
    Utility u;
        int MoveSpeed;
        int MoveCount;

        string defaultimage[12][1] = {
            {Yellow"■" Reset},
            {BgWhite TextYellow"▼" Reset},
            {BgWhite TextYellow"▼" Reset},
            {BgWhite TextYellow"▼" Reset},
            {BgBlack" " BgWhite" " Reset},
            {BgBlack" " BgWhite" " Reset},
            {BgBlack" " BgWhite" " Reset},
            {BgBlack" " BgWhite" " Reset},
            {BgBlack" " BgWhite" " Reset},
            {BgBlack" " BgWhite" " Reset},
            {BgBlack" " BgWhite" " Reset},
            {BgBlack" " BgWhite" " Reset}
        };

        Sword(int x, int y, int width, int height) : Object(width, height) {
            X = x;
            Y = y;
            Active = true;
            Width = width;
            Height = height;
            ImagePaste();
        }

        void ImagePaste() {
            for (int i = 0; i < 12; i++) {
                    image[i][0] = defaultimage[i][0];
            }
        }

        void Render(Scene& s) {
            for (int i = 0; i < Height; i++){
                if ((Y + i) < 39){
                    for (int j = 0; j < Width; j++){
                        if (0 <= (X + j) && (X + j) < 100){
                            if (image[i][j] != "  "){
                                s.ScreenBuffer[Y + i][X + j] = image[i][j];
                            }
                        }
                    }
                }
            }
        }

        void MoveSword() {
                    X--;
                    if (X + Width < 0) {
                        X = 100;
                    }
        }
};

int main() {

    system("mode con cols=202 lines=42");

    Utility u;
    Scene s;

    Player p(5, 25, 10, 10);
    
    Cloud c1(30, 5, 15, 8, 1);
    Cloud c2(70, 8, 15, 8, 2);
    Cloud c3(10, 10, 15, 8, 3);

    Ground g(100, 4);

    Mountain m(20, 17, 55, 22);

    Sword sw( 90 , 27, 1, 12);

    int speed = 1;
    int score = 0;

    s.AddObject(m);
    s.AddObject(c1);
    s.AddObject(c2);
    s.AddObject(c3);
    s.AddObject(sw);
    s.AddObject(g);
    s.AddObject(p);

    while (true) {
        u.gotoxy(0, 0);

        auto startTime = chrono::high_resolution_clock::now();


        s.ClearScreenBuf();
        if (_kbhit()) {
            char key = _getch();
            if (key == ' ') {
                p.IsJump = true;
            }
        }
        p.JumpPlayer();
        //p.MovePlayer();
        c1.MoveCloud();
        c2.MoveCloud();
        c3.MoveCloud();
        m.MoveMountain();
        g.MoveGround();
        sw.MoveSword();
        s.Draw(score, speed);

        auto endTime = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsedTime = endTime - startTime;

        double targetFrameTime = 1.0 / elapsedTime.count();
        cout << " Fps: " << targetFrameTime << endl;

        score++;
        if (score % 100 == 0) {
            speed++;
        }
    }
    return 0;
}
