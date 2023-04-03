#include <iostream>
#include <windows.h>

using namespace std;

// 노드 클래스
class Node {
public:
    int valueX; // 노드에 저장하는 맵의 x값
    int valueY; // 노드에 저장하는 맵의 y값
    int index;  // 노드의 인덱스 값
    int parentIndex; // 부모 노드의 인덱스 값
    Node* _1stChild; // 1번째 자식 노드 포인터
    Node* _2ndChild; // 2번째 자식 노드 포인터
    Node* _3rdChild; // 3번째 자식 노드 포인터
    Node* _4thChild; //4번째 자식노드 포인터

    Node(int x, int y, int i, int p) { // x값 ,y값, 번호, 부모번호, count(최단경로 길이 체크용)
        valueX = x;
        valueY = y;
        index = i;
        parentIndex = p;
        _1stChild = NULL;
        _2ndChild = NULL;
        _3rdChild = NULL;
        _4thChild = NULL;
    }

    // 자식 노드 생성자
    Node(int x, int y, int i, int p, Node* parent) {
        valueX = x;
        valueY = y;
        index = i;
        parentIndex = p;
        _1stChild = NULL;
        _2ndChild = NULL;
        _3rdChild = NULL;
        _4thChild = NULL;

        // 부모 노드와 자식 노드를 연결합니다.
        if (parent != NULL) {
            if (parent->_1stChild == NULL) {
                parent->_1stChild = this;
            }
            else if(parent->_2ndChild == NULL) {
                parent->_2ndChild = this;
            }
            else if (parent->_3rdChild == NULL) {
                parent->_3rdChild = this;
            }
            else {
                parent->_4thChild = this;
            }
        }
    }
};

// 트리 클래스
class Tree {
public:
    Node* root; // 루트 노드 포인터

    // 루트 노드 생성자
    Tree(int x, int y) {
        root = new Node(x, y, 0, -1); // 루트 노드는 인덱스가 0이고 부모 노드가 없습니다.
    }

    // 노드 삽입 함수
    void insertNode(int x, int y, int i, int p) {
        Node* node = new Node(x, y, i, p, findParentNode(p)); // 노드 생성자를 호출해 새로운 노드를 만듭니다.
    }

    // 부모 노드 검색 함수
    Node* findParentNode(int p) {
        if (p == -1) {
            return NULL; // 부모 노드가 없으면 NULL을 반환합니다.
        }
        else {
            return findNode(root, p); // 루트 노드부터 시작해 부모 노드를 찾습니다.
        }
    }

    // 노드를 찾는 함수
    Node* findNode(Node* currentNode, int i) {
        if (currentNode == NULL) { // 현재 노드가 NULL이면
            return NULL; // NULL을 반환
        }
        else if (currentNode->index == i) { // 현재 노드의 인덱스가 찾는 인덱스와 같으면
            return currentNode; // 현재 노드를 반환
        }
        else {
            Node* _1stNode = findNode(currentNode->_1stChild, i); // 왼쪽 자식 노드에서 찾기
            Node* _2ndNode = findNode(currentNode->_2ndChild, i); // 중간자식 노드에서 찾기
            Node* _3rdNode = findNode(currentNode->_3rdChild, i); // 오른쪽 자식 노드에서 찾기
            Node* _4thNode = findNode(currentNode->_4thChild, i); // 오른쪽 자식 노드에서 찾기

            if (_1stNode != NULL) { // 왼쪽 자식 노드에서 찾은 경우
                return _1stNode; // 왼쪽 자식 노드를 반환
            }
            else if (_2ndNode != NULL) { // 중간 자식 노드에서 찾은 경우
                return _2ndNode; // 중간 자식 노드를 반환
            }
            else if (_3rdNode != NULL) { // 오른쪽 자식 노드에서 찾은 경우
                return _3rdNode; // 오른쪽 자식 노드를 반환
            }
            else if (_4thNode != NULL) { // 4번째 자식 노드에서 찾은 경우
                return _4thNode; // 4번째 자식 노드를 반환
            }
            else { // 찾는 노드가 없는 경우
                return NULL; // NULL을 반환
            }
        }
    }
};

class Map {
public : 
    
    /* 좌표 = {
    *      x - >             array[y][x]
        y { 0, 0, 0, 0, 0},
        | { 0, 0, 0, 0, 0},
        ˅ { 0, 0, 0, 0, 0},
          { 0, 0, 0, 0, 0},
          { 0, 0, 0, 0, 0}
    };*/

    int mapData[5][5] = { //벽은 0, 갈수있는길은 1, 플레이어는 2, 적은 3, 최단경로는 4
        { 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1}
    };

    int maplog[5][5] = { //벽 및 가지말아야 할 길은 -1, 갈수있는길은 -2, 플레이어는 0, 경로는 숫자로 +1씩
        { -2, -2, -2, -2, -2},
        { -2, -2, -2, -2, -2},
        { -2, -2, -2, -2, -2},
        { -2, -2, -2, -2, -2},
        { -2, -2, -2, -2, -2}
    };

    bool mapUse[5][5] = { //최단경로 설정시 이미 지나간길, 지나갈 수 없는길 표시
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0}
    };

    Map(int playerX, int playerY, int enemyX, int enemyY) { // 맵을 생성하면 적의 위치와 플레이어의 위치를 처음부터 지정
        mapData[playerY][playerX] = 2;
        mapUse[playerY][playerX] = 1;
        maplog[playerY][playerX] = 0;
        mapData[enemyY][enemyX] = 3;
        mapUse[enemyY][enemyX] = 1;
    }

    void wallCreat(int wallX, int wallY) { // 벽생성
        if (mapData[wallY][wallX] == 1) {
            mapData[wallY][wallX] = 0;
            mapUse[wallY][wallX] = 1;
            maplog[wallY][wallX] = -1;
        }
        else {
            cout << "벽으로 바꿀수 없습니다." << endl;
        }
    }

    void roadCreat(int roadX, int roadY) { // 길생성
        if (mapData[roadY][roadX] == 0) {
            mapData[roadY][roadX] = 1;
            mapUse[roadY][roadX] = 0;
            maplog[roadY][roadX] = -2;
        }
        else {
            cout << "길로 바꿀수 없습니다." << endl;
        }
    }

    void mapclear() {
        system("cls");
    }

    void mapPrint() {
        mapclear();
        //벽은 0, 갈수있는길은 1, 플레이어는 2, 적은 3, 최단경로는 4
        for (int i = 0; i < 5; i++) { //벽 : ▣, 길 : □, 플레이어 : ●, 적 : ★, 경로 : ◆
            for (int j = 0; j < 5; j++) {
                if (mapData[i][j] == 0){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    cout << "▣";
                } else if (mapData[i][j] == 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                    cout << "□";
                } else if (mapData[i][j] == 2) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                    cout << "●";
                } else if (mapData[i][j] == 3) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << "★";
                } else if (mapData[i][j] == 4) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    cout << "◆";
                }
            }
            cout << endl;
        }
    }

    int findEnemy() {
        int pos;
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                if (mapData[i][j] == 3){
                    pos = i * 5 + j;
                    return pos;
                }
            }
        }
    }

    int findPlayer() {
        int pos;
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                if (mapData[i][j] == 2){
                    pos = i * 5 + j;
                    return pos;
                }
            }
        }
    }
};

void route(Map &m) {
    int X;
    int Y;
    int index = 0;
    int tempindex = 0;
    int a;
    int log = 0;
    Y = m.findPlayer() / 5;
    X = m.findPlayer() % 5;
    Tree t(X, Y); //시작점 루트로 트리 생성
    void insertNode(int x, int y, int i, int p);

    //위오아왼
    while (true)
    {   
        if (X < 4 && m.mapUse[Y][X + 1] != 1) { //오 
            t.insertNode(X + 1, Y, tempindex + 1, index);
            tempindex += 1;
            log += 1;
            m.mapData[Y][X + 1] = 4;
            m.mapUse[Y][X + 1] = 1;
            m.maplog[Y][X + 1] = log;
            m.mapPrint();
        
        }
         else if (Y < 4 && m.mapUse[Y + 1][X] != 1) { //아래 
            t.insertNode(X, Y + 1, tempindex + 1, index);
            tempindex += 1;
            log += 1;
            m.mapData[Y + 1][X] = 4;
            m.mapUse[Y + 1][X] = 1;
            m.maplog[Y + 1][X] = log;
            m.mapPrint();
        }   else if (Y > 0 && m.mapUse[Y - 1][X] != 1) { //위 
            t.insertNode(X, Y - 1, tempindex + 1, index);
            tempindex += 1;
            log += 1;
            m.mapData[Y - 1][X] = 4;
            m.mapUse[Y - 1][X] = 1;
            m.maplog[Y - 1][X] = log;
            m.mapPrint();
        }
        else if (X > 0 && m.mapUse[Y][X - 1] != 1) { //왼 
            t.insertNode(X - 1, Y, tempindex + 1, index);
            tempindex += 1;
            log += 1;
            m.mapData[Y][X - 1] = 4;
            m.mapUse[Y][X - 1] = 1;
            m.maplog[Y][X - 1] = log;
            m.mapPrint();
        }
        else if (m.maplog[Y][X + 1] != -2 && m.maplog[Y][X - 1] != -2 && m.maplog[Y + 1][X] != -2 && m.maplog[Y - 1][X] != -2) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (m.maplog[i][j] == log) {
                        m.mapData[Y][X] = 1;
                        X = j;
                        Y = i;
                        log = log - 1;
                        index = index - 1;
                        i = 5;
                        j = 5;
                    }
                }
            }
            m.mapPrint();
            continue;
        } else {
            if (m.mapData[Y][X + 1] == 3 || m.mapData[Y][X - 1] == 3 || m.mapData[Y + 1][X] == 3 || m.mapData[Y - 1][X] == 3) {
                cout << "적에게 도달했습니다.";
                break;
            }
            cout << "적에게 도달할 수 없습니다." << endl;
            break;
        }
        index = tempindex;
        Y = t.findParentNode(index)->valueY;
        X = t.findParentNode(index)->valueX;
    }
}

int main() {
    Map map(0,4,3,4);
    map.wallCreat(2,1);
    map.wallCreat(2,2);
    map.wallCreat(3,2);
    map.wallCreat(2,3);
    map.wallCreat(2,4);
    map.mapPrint();
    route(map);
    return 0;
    }

/* 좌표 = {
*      x - >             array[y][x]
    y { 0, 0, 0, 0, 0},
    | { 0, 0, 0, 0, 0},
    ˅ { 0, 0, 0, 0, 0},
      { 0, 0, 0, 0, 0},
      { 0, 0, 0, 0, 0}
};*/
