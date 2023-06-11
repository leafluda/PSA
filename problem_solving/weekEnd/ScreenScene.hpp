#pragma once
#include "GameObject.hpp"

using namespace std;

    class Scene {

    public:

        string Output; // 출력용
        string ScreenBuffer[39][100]; // x 100, y 40
        vector<Object*> Objects;

        Scene() {
            Output = "";
            ClearScreenBuf();
        }

        // Active한 Object의 Render를 호출해 ScreenBuffer에 저장하고 ScreenBuffer 출력
        void Draw() {
            for (Object* obj : Objects) {
                if (obj->Active == true) {
                    obj->Render(*this);
                }
            }           
            Output = "";
            for (int i = 0; i < 39; i++) {
                for (int j = 0; j < 100; j++) {
                    Output += ScreenBuffer[i][j];
                }
                Output += Reset"\n";
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

        void ResetObject() {
            for (Object* obj : Objects) {
                if (obj->Active == true) {
                    obj->ResetPos();
                }
            }
        }

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
