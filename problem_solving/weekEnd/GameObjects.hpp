#pragma once
#include "ScreenScene.hpp"

using namespace std;

class Scene;   

    class Cloud : public Object {
    public:
        int MoveCount;
        int MoveSpeed;

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

        string DefaultImage[7][15] = {
            {"  ","  ","  ","  ","  ","  ","■","■","  ","  ","  ","  ","  ","  ","  "},

            {"  ","  ","■","■","  ","■","■","■","■","  ","  ","▦","■","  ","  "},

            {"  ","■","■","■","■","■","■","■","■","  ","▦","■","■",White "■" Reset,"  "},

            {"  ","■","■","■","▦","■","■","■","■","▦","■","■","■","■",White "■" Reset},

            {"▦","▦","■","▦","▦","■","■","■","▦","▦","▦","■","■","■",Lgray"▦" Reset},

            {"▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦",Lgray "▦" Reset},

            {"  ","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦","▦",Lgray"▦" Reset,"  "}
        };

        void setActive(bool b) {
            Active = b;
        }

        void ResetPos() {
            X = DefaultX;
            Y = DefaultY;
            Active = true;
            MoveCount = 0;
        }

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

        void ImagePaste() {
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 15; j++) {
                    if (DefaultImage[i][j] == "■") {
                        if (j < 14 && DefaultImage[i][j + 1] == "  ")
                        {
                            DefaultImage[i][j] = White"■" Reset;
                        }
                        else
                        {
                            DefaultImage[i][j] = White"■";
                        }
                    }
                    else if (DefaultImage[i][j] == "▦") {
                        if (j < 14 && DefaultImage[i][j + 1] == "  ")
                        {
                            DefaultImage[i][j] = Lgray"▦" Reset;
                        }
                        else
                        {
                            DefaultImage[i][j] = Lgray"▦";
                        }
                    }
                    Image[i][j] = DefaultImage[i][j];
                }
            }
        }

        void MoveCloud() {

            if (MoveCount > 10) {
                X--;
                if (MoveCount > 15)
                {
                X--;
                }
                if (X + Width < 0) {
                    X = 100;
                }
                MoveCount = 0;
            }
            else {
                MoveCount = MoveCount + speed + MoveSpeed;
            }
        }

        void SpeedUp(int GameSpeed)
        {
            speed = GameSpeed;
        }
    };

    class Mountain : public Object {
    public:
        int MoveCount;

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

        void setActive(bool b) {
            Active = b;
        }

        void ResetPos() {
            X = DefaultX;
            Y = DefaultY;
            Active = true;
            MoveCount = 0;
        }

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

        void ImagePaste() {
            for (int i = 0; i < 22; i++) {
                for (int j = 0; j < 46; j++) {
                    if (DefaultImage[i][j] == "■") {
                        if (j < 45 && DefaultImage[i][j + 1] == "  ")
                        {
                            DefaultImage[i][j] = White"■" Reset;
                        }
                        else
                        {
                            DefaultImage[i][j] = White"■";
                        }
                    }
                    else if (DefaultImage[i][j] == "▣") {
                        if (j < 45 && DefaultImage[i][j + 1] == "  ")
                        {
                            DefaultImage[i][j] = Lgray"▣" Reset;
                        }
                        else
                        {
                            DefaultImage[i][j] = Lgray"▣";
                        }
                    }
                    else if (DefaultImage[i][j] == "▧") {
                        if (j < 45 && DefaultImage[i][j + 1] == "  ")
                        {
                            DefaultImage[i][j] = Gray"▧" Reset;
                        }
                        else
                        {
                            DefaultImage[i][j] = Gray"▧";
                        }
                    }
                    Image[i][j] = DefaultImage[i][j];
                }
            }
        }

        void MoveMountain() {
            if (MoveCount > 50) {
                X--;
                if (X + Width < 0) {
                    X = 100;
                }
                MoveCount = 0;
            }
            else {
                MoveCount = MoveCount + speed + 1;
            }
        }

        void SpeedUp(int GameSpeed)
        {
            speed = GameSpeed;
        }
    };

    class Ground : public Object {

    public:
        int FlowerCount;

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

        string tempImage[4][100];

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

        void setActive(bool b) {
            Active = b;
        }

        void ResetPos() {
            X = DefaultX;
            Y = DefaultY;
            Active = true;
            FlowerCount = 0;
        }


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

    class Sword : public Object {
    public:
        int MoveSpeed;
        int MoveCount;
        bool IsFalling;
        bool DefaultType;
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

        void ImagePaste() {
            for (int i = 0; i < 12; i++) {
                Image[i][0] = DefaultImage[i][0];
            }
        }

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

        void ResetPos() {
            X = DefaultX;
            Y = DefaultY;
            Active = false;
            IsFalling = DefaultType;
        }

        void setActive(bool b) {
            Active = b;
        }

        void MoveSword() {
            if (IsFalling == false) {
                for (int s = -1; s < speed; s++)
                {
                    X--;
                    if (X + Width < 0) {
                        ResetPos();
                        break;
                    }
                }                 
            }
        }

        void FallingSword() {
            if (IsFalling == true) {
                for (int s = -1; s < speed; s++)
                {
                    Y++;
                    if (Y > 26) {
                        IsFalling = false;
                        break;
                    }
                }
            }
        }

        void SpeedUp(int GameSpeed)
        {
            speed = GameSpeed;
        }
    };

    class Player : public Object
    {

    public:
        int MoveCount;
        bool IsJump;
        bool IsFalling;
        int JumpCount;

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

        void Render(Scene& s) {
            for (int i = 0; i < Height; i++)
            {
                for (int j = 0; j < Width; j++)
                {
                    if (Image[i][j] != "  ")
                    {
                        s.ScreenBuffer[Y + i][X + j] = Image[i][j];
                    }
                }
            }
        }

        void ResetPos()
        {
            Active = true;
            MoveCount = 0;
            JumpCount = 0;
            IsFalling = false;
            IsJump = false;
            Y = DefaultY;
        }


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
                    }
                    else if (DefaultImage[i][j] == "▤") {
                        DefaultImage[i][j] = White"▤" Reset;
                    }
                    else if (DefaultImage[i][j] == "□") {
                        DefaultImage[i][j] = Mint"□" Reset;
                    }
                    else if (DefaultImage[i][j] == "▧") {
                        DefaultImage[i][j] = Lblue"▧" Reset;
                    }
                    else if (DefaultImage[i][j] == "▲" || DefaultImage[i][j] == "▣") {
                        DefaultImage[i][j] = TextBlack BgLmint + DefaultImage[i][j];
                    }
                    Image[i][j] = DefaultImage[i][j];
                }
            }
        }

        void MovePlayer() {
            if (IsJump == false) {
                if (MoveCount < 4) {
                    Y--;
                    MoveCount++;
                }
                else {
                    Y++;
                    MoveCount++;
                    if (MoveCount >= 8) {
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
                        if (JumpCount >= 15) {
                            IsFalling = true;
                        }                    
                }
                else if (IsFalling == true) {
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

        bool Collider(Sword& sw) { // 교체

            if (sw.X >= X + 2 && sw.X <= X + 6) {
                if ((Y + 9) >= 27) {
                    return true;
                }
            }
            else if (sw.X == X + 1 || sw.X == X + 7 || sw.X == X + 8)
            {
                if ((Y + 9) >= 28) {
                    return true;
                }
            }
            else if (sw.X == X || sw.X == X + 9)
            {
                if ((Y + 9) >= 29) {
                    return true;
                }
            }
        }

        void SpeedUp(int GameSpeed)
        {
            speed = GameSpeed;
        }
    };
