#pragma once
#include "Utility.hpp"
#include "GameObject.hpp"
#include "ScreenScene.hpp"
#include "GameObjects.hpp"
#include "GameObjectUI.hpp"
#include "Gamestage.hpp"

Scene GameScene; // 게임시작시 보여지는 화면
Scene MainScene; // 메인화면

Stage stage; // 스테이지 저장용 객체
Player player(5, 25, 10, 10); // 플레이어 객체
MemoryPool<Sword> swordpool(10); // 장애물 오브젝트 풀링
vector<Sword*> usingsword; // 사용하는 장애물을 저장하는 배열
MemoryPool<Cloud> cloudpool(3); // 구름 오브젝트 풀링
vector<Cloud*> usingcloud; // 사용하는 구름을 저장하는 배열

Ground ground(100, 4); // 땅 객체
Mountain mountain(20, 13, 46, 22); // 산 객체

PauseUi pauseui(31, 10, 38, 18); // 일시정지 ui
GameOverUi gameoverui(31, 10, 38, 18); // 게임오버 ui

StartUi startui(10, 5, 80, 30); // 게임 메인화면 ui
Arrow arrow(46, 17, 7, 7); // 화살표 ui
Rules rules(30, 5, 40, 30); // 게임 방법 ui
Ranks ranks(30, 5, 40, 30); // 순위표 ui

string leaderboard = "LeaderBoard.txt"; // 순위표 파일
string stagefile = "1.txt"; // 스테이지 파일
string name = ""; // 순위 저장용 이름 변수

int speed = 0; // 게임 속도
int score = 0; // 점수
int StageSequence = 0; // 스테이지 장애물 등장 순서
int stagenumber = stoi(stagefile.substr(0, stagefile.find("."))); // 순위 저장용 스테이지 번호 변수 

bool SwordCount = false; // 장애물을 생성해야 할때만 true;
bool IsStart = false; // 메인화면, 게임화면을 구분하는 변수;
bool Pause = false; // 일시정지인지 아닌지 판단하는 변수
bool CloseProgram = false; // gameloop의 동작을 판단하는 변수
bool Collision = false; // 충돌했는지 판단하는 변수

class GameEngine {

public:

    // 생성자로 게임초기 설정에 필요한 함수 호출
    GameEngine() {
        stage.readDataFromFile(stagefile);
        ranks.readDataFromFile(leaderboard);
        GameScene.AddObject(mountain);
        GameScene.AddObject(ground);
        GameScene.AddObject(player);
        GameScene.AddObject(pauseui);
        GameScene.AddObject(gameoverui);

        MainScene.AddObject(startui);
        MainScene.AddObject(arrow);
        MainScene.AddObject(rules);
        MainScene.AddObject(ranks);
    }

    // 게임루프 
    void GameRun() {
        while (!CloseProgram) {
            if (IsStart == true) {
                GameLoop();
            } else if (IsStart == false) {
                MainLoop();
            }
        }
    }

    // 메인화면 루프
    void MainLoop() {
        GoToXY(0, 0);

        auto startTime = chrono::high_resolution_clock::now(); // 렌더링 시작시간 측정

        MainScene.ClearScreenBuf(); // MainScene.ScreenBuffer초기화

        //키를 누르면 반응
        if (_kbhit()) { 
            char key = _getch();
            if (key == 80 && arrow.UpDown) { // 아래 방향키
                arrow.Y += 10;
                arrow.UpDown = false;
            } else if (key == 72 && !arrow.UpDown) { // 윗 방향키
                arrow.Y -= 10;
                arrow.UpDown = true;
            } else if (key == 75 && !arrow.LeftRight) { // 왼쪽 방향키
                arrow.LeftRight = true;
                arrow.ImagePaste();
            } else if (key == 77 && arrow.LeftRight) { // 오른쪽 방향키
                arrow.LeftRight = false;
                arrow.ImagePaste();
            } else if (key == 13 && !arrow.UpDown && arrow.LeftRight) { // 프로그램 종료
                CloseProgram = true;
            } else if (key == 13 && arrow.UpDown && arrow.LeftRight) { // 게임 시작
                GameScene.ResetObject();
                GameScene.SpeedObject(speed);
                IsStart = true;
            } else if (key == 13 && !arrow.LeftRight && !arrow.UpDown) { // 순위표 출력
                ranks.setActive(!ranks.Active);
                ranks.loadingLeaderBoard();
            } else if (key == 13 && !arrow.LeftRight && arrow.UpDown) { // 게임 방법 출력
                rules.setActive(!rules.Active);
            }
        }
        MainScene.Draw(); // Rendering

        auto endTime = chrono::high_resolution_clock::now(); // 렌더링 종료시간 측정
        chrono::duration<double> elapsedTime = endTime - startTime; // 차이를 계산
        double targetFrameTime = 1.0 / 60; // 60프레임을 기준으로
        double sleepTime = targetFrameTime - elapsedTime.count(); // 차이를 계산
        if (sleepTime > 0) { // 양수라면 그만큼 sleep
            this_thread::sleep_for(chrono::duration<double>(sleepTime));
        }
    }

    // 게임화면 루프
    void GameLoop() {
        GoToXY(0, 0);

        auto startTime = chrono::high_resolution_clock::now(); // 렌더링 시작시간 측정

        GameScene.ClearScreenBuf(); // GameScene.ScreenBuffer초기화

        // P or p키를 누르면 pause
        if (_kbhit()) {
            char key = _getch();
            if (key == ' ') {
                player.IsJump = true;
            } else if (key == 'p' || key == 'P') {
                Pause = true;
                pauseui.setActive(true);
            }
        }

        // 객체 이동 함수 호출
        player.JumpPlayer();
        player.MovePlayer();
        mountain.MoveMountain();
        ground.MoveGround();

        // stage의 순서에 따라서 장애물 생성
        if (SwordCount == true) {
            if (stage.StageArray[StageSequence] == 1) {
                Sword* sword = new (swordpool.Acquire()) Sword(99, 27, 1, 12, false);
                usingsword.push_back(sword);
                GameScene.InsertObject(*usingsword.back());
                SwordCount = false;
            } else if (stage.StageArray[StageSequence] == 2) {
                Sword* fallingsword = new (swordpool.Acquire()) Sword(99, 1, 1, 12, true);
                usingsword.push_back(fallingsword);
                GameScene.InsertObject(*usingsword.back());
                SwordCount = false;
            }
        }

        // 장애물 객체마다 이동 함수 호출
        for (int i = 0; i < usingsword.size(); i++) {
            if (usingsword[i]->Active == true) {
                if (usingsword[i]->DefaultType == true) {
                    usingsword[i]->FallingSword();
                    usingsword[i]->MoveSword();
                } else if (usingsword[i]->DefaultType == false) {
                    usingsword[i]->MoveSword();
                }
            } else if (usingsword[i]->Active == false) {
                swordpool.Release(usingsword[i]);
                usingsword.erase(usingsword.begin() + i);
            }
        }

        // 구름 객체마다 이동 함수 호출
        for (int i = 0; i < usingcloud.size(); i++) {            
            usingcloud[i]->MoveCloud();       
        }

        GameScene.Draw(); // Rendering
        cout << "점수 : " << score << " , 속도 : " << speed; // 점수, 속도 표시

        // 충돌 체크
        for (int i = 0; i < usingsword.size(); i++) {
            Collision = player.Collider(*usingsword[i]);
            if (Collision == true) {
                break;
            }
        }

        // 단 하나의 장애물 객체라도 플레이어와 충돌했다면 게임오버
        if (Collision == true) {
            gameoverui.GameOverSituation(GameScene, 2);
            GameOver();
        }

        // P,p키를 눌렀다면 pause
        if (Pause == true) {
            while (Pause) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == 'p' || key == 'P') {
                        Pause = false;
                    }
                }
            }
            pauseui.PauseGame(GameScene);
        }

        // 렌더링 마다 점수 추가
        score++;

        // 속도에 따라서 몇번 렌더링 할때마다 장애물 생성, 장애물을 더 이상 소환 못한다면, player win
        if (score % (60-(speed*10)) == 0) {
            SwordCount = true;
            StageSequence++;
            if (StageSequence > stage.StageLength && usingsword.size() == 0) {
                gameoverui.GameOverSituation(GameScene, 3);
                GameOver();
            }
        }

        // 500점 마다 속도 증가, 그때마다 구름을 생성
        if (score % 500 == 0) {
            if (speed < 6) {
                speed++;
                Cloud* cloud = new (cloudpool.Acquire()) Cloud(speed*10, speed*3, 15, 7, speed);
                usingcloud.push_back(cloud);
                GameScene.InsertObject(*usingcloud.back());
                GameScene.SpeedObject(speed);
            }
        }

        auto endTime = chrono::high_resolution_clock::now(); // 렌더링 종료시간 측정
        chrono::duration<double> elapsedTime = endTime - startTime; // 차이를 계산
        double targetFrameTime = 1.0 / 60; // 60프레임을 기준으로
        double sleepTime = targetFrameTime - elapsedTime.count(); // 차이를 계산
        if (sleepTime > 0) {
            this_thread::sleep_for(chrono::duration<double>(sleepTime)); // 양수라면 그만큼 sleep
        }
    }

    // 게임오버시 실행되는 동작
    void GameOver() {
        cout << "이름을 입력하시오(5글자 제한, 띄어쓰기 불가) : ";
        cin >> name; // 이름을 저장
        GoToXY(0, 39); // 점수와 속도, 이름을 지움 system("cls") 대신 사용
        cout << "                                                                     ";
        ranks.writeLeaderBoard(name, score, stagenumber); // 순위표에 기록
        ranks.writeDataToFile(leaderboard); // 순위표를 업데이트
        gameoverui.GameOverSituation(GameScene, 1); // 게임재시작 여부 질문
        int select = 1;

        // 키를 엔터키를 입력할때까지 계속 질문, 좌우 방향키로 선택
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 75) {
                    select = 1;
                    gameoverui.GameOverSituation(GameScene, select);
                } else if (key == 77) {
                    select = 0;
                    gameoverui.GameOverSituation(GameScene, select);
                } else if (key == 13) {
                    break;
                }
            }
        }

        // 게임 변수 초기화
        speed = 0;
        score = 0;
        GameScene.ResetObject();
        GameScene.SpeedObject(speed);
        Collision = false;

        // no를 선택시 메인 화면으로
        if (select == 0) {
            IsStart = false;
        }
    }
};
