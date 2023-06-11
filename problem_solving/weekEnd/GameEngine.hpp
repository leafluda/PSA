#pragma once
#include "Utility.hpp"
#include "GameObject.hpp"
#include "ScreenScene.hpp"
#include "GameObjects.hpp"
#include "GameObjectUI.hpp"
#include "Gamestage.hpp"

Scene GameScene;
Scene MainScene;

Stage stage;
Player player(5, 25, 10, 10);
MemoryPool<Sword> swordpool(10);
vector<Sword*> usingsword;
MemoryPool<Cloud> cloudpool(3);
vector<Cloud*> usingcloud;

Ground ground(100, 4);
Mountain mountain(20, 13, 46, 22);

PauseUi pauseui(31, 10, 38, 18);
GameOverUI gameoverui(31, 10, 38, 18);

StartUI startui(10, 5, 80, 30);
Arrow arrow(46, 17, 7, 7);
Rules rules(30, 5, 40, 30);
Ranks ranks(30, 5, 40, 30);

string leaderboard = "LeaderBoard.txt";
string stagefile = "1.txt";
string name = "";

int speed = 0;
int score = 0;
int StageSequence = 0;
int stagenumber = stoi(stagefile.substr(0, stagefile.find(".")));

bool SwordCount = false;
bool IsStart = false;
bool Pause = false;
bool CloseProgram = false;
bool Collision = false;

class GameEngine
{
public:
    GameEngine()
    {
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

    void GameRun() {

        Loop();
    }

    void Loop() {
        while (!CloseProgram) {
            if (IsStart == true) {
                GameLoop();
            }
            else if (IsStart == false)
            {
                MainLoop();
            }
        }

    }

    void MainLoop()
    {
        GoToXY(0, 0);

        auto startTime = chrono::high_resolution_clock::now();

        MainScene.ClearScreenBuf();

        if (_kbhit()) {
            char key = _getch();
            if (key == 80 && arrow.UpDown) {
                arrow.Y += 10;
                arrow.UpDown = false;
            }
            else if (key == 72 && !arrow.UpDown) {
                arrow.Y -= 10;
                arrow.UpDown = true;
            }
            else if (key == 13 && !arrow.UpDown && arrow.LeftRight) {
                CloseProgram = true;
            }
            else if (key == 13 && arrow.UpDown && arrow.LeftRight) {
                GameScene.ResetObject();
                GameScene.SpeedObject(speed);
                IsStart = true;
            }
            else if (key == 13 && !arrow.LeftRight && !arrow.UpDown) {
                ranks.setActive(!ranks.Active);
                ranks.loadingLeaderBoard();
            }
            else if (key == 13 && !arrow.LeftRight && arrow.UpDown) {
                rules.setActive(!rules.Active);
            }
            else if (key == 75 && !arrow.LeftRight) {
                arrow.LeftRight = true;
                arrow.ImagePaste();
            }
            else if (key == 77 && arrow.LeftRight) {
                arrow.LeftRight = false;
                arrow.ImagePaste();
            }
        }
        MainScene.Draw();

        auto endTime = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsedTime = endTime - startTime;

        double targetFrameTime = 1.0 / 60;

        double sleepTime = targetFrameTime - elapsedTime.count();
        if (sleepTime > 0) {
            this_thread::sleep_for(chrono::duration<double>(sleepTime));
        }
    }

    void GameLoop()
    {
        GoToXY(0, 0);

        auto startTime = chrono::high_resolution_clock::now();

        GameScene.ClearScreenBuf();
        if (_kbhit()) {
            char key = _getch();
            if (key == ' ') {
                player.IsJump = true;
            }
            else if (key == 'p' || key == 'P') {
                Pause = true;
                pauseui.setActive(true);
            }
        }
        player.JumpPlayer();
        player.MovePlayer();
        mountain.MoveMountain();
        ground.MoveGround();

        if (SwordCount == true)
        {
            if (stage.StageArray[StageSequence] == 1)
            {
                Sword* sword = new (swordpool.Acquire()) Sword(99, 27, 1, 12, false);
                usingsword.push_back(sword);
                GameScene.InsertObject(*usingsword.back());
                SwordCount = false;
            }
            else if (stage.StageArray[StageSequence] == 2)
            {
                Sword* fallingsword = new (swordpool.Acquire()) Sword(99, 1, 1, 12, true);
                usingsword.push_back(fallingsword);
                GameScene.InsertObject(*usingsword.back());
                SwordCount = false;
            }
        }

        for (int i = 0; i < usingsword.size(); i++)
        {
            if (usingsword[i]->Active == true)
            {
                if (usingsword[i]->DefaultType == true)
                {
                    usingsword[i]->FallingSword();
                    usingsword[i]->MoveSword();
                }
                else if (usingsword[i]->DefaultType == false)
                {
                    usingsword[i]->MoveSword();
                }
            }
            else if (usingsword[i]->Active == false)
            {
                swordpool.Release(usingsword[i]);
                usingsword.erase(usingsword.begin() + i);
            }
        }
        for (int i = 0; i < usingcloud.size(); i++)
        {            
            usingcloud[i]->MoveCloud();       
        }

        GameScene.Draw();
        cout << "점수 : " << score << " , 속도 : " << speed;

        /*for (int i = 0; i < usingsword.size(); i++)
        {
            Collision = player.Collider(*usingsword[i]);
            if (Collision == true)
            {
                break;
            }
        }
        if (Collision == true) {
            gameoverui.GameOverSituation(GameScene, 2);
            GameOver();
        }*/
        auto endTime = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsedTime = endTime - startTime;

        double targetFrameTime = 1.0 / 60;

        double sleepTime = targetFrameTime - elapsedTime.count();
        if (sleepTime > 0) {
            this_thread::sleep_for(chrono::duration<double>(sleepTime));
        }

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

        score++;
        if (score % (60-(speed*10)) == 0) {
            SwordCount = true;
            StageSequence++;
            if (StageSequence > stage.StageLength && usingsword.size() == 0) {
                gameoverui.GameOverSituation(GameScene, 3);
                GameOver();
            }
        }
        if (score % 200 == 0) {
            if (speed < 6)
            {
                speed++;
                Cloud* cloud = new (cloudpool.Acquire()) Cloud(speed*10, speed*3, 15, 7, speed);
                usingcloud.push_back(cloud);
                GameScene.InsertObject(*usingcloud.back());
                GameScene.SpeedObject(speed);
            }
        }
    }

    void GameOver() {
        cout << "이름을 입력하시오(5글자 제한, 띄어쓰기 불가) : ";
        cin >> name;
        GoToXY(0, 39);
        cout << "                                                                     ";
        ranks.writeLeaderBoard(name, score, stagenumber);
        ranks.writeDataToFile(leaderboard);
        gameoverui.GameOverSituation(GameScene, 1);
        int select = 1;
        while (true)
        {
            if (_kbhit()) {
                char key = _getch();
                if (key == 75)
                {
                    select = 1;
                    gameoverui.GameOverSituation(GameScene, select);
                }
                else if (key == 77)
                {
                    select = 0;
                    gameoverui.GameOverSituation(GameScene, select);
                }
                else if (key == 13)
                {
                    break;
                }
            }
        }
        speed = 0;
        score = 0;
        GameScene.ResetObject();
        GameScene.SpeedObject(speed);
        Collision = false;
        if (select == 0) {
            IsStart = false;
        }
    }
};
