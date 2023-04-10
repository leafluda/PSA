#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>
#include <conio.h>

using namespace std;

const int MAXN = 10;
const int INF = 1e9;

int keypress() {
    while (true) {
        while (!_kbhit()) { // 키보드 입력을 대기
        }
        break;
    }
    return 0;
}

class Map {
public:
    int map[10][10];
    int player_x, player_y;
    int enemy_x, enemy_y;

public:
    Map() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = 0;
            }
        }
        player_x = -1;
        player_y = -1;
        enemy_x = -1;
        enemy_y = -1;
    }

    void reset_path() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (map[i][j] == 4) {
                    map[i][j] = 0;
                }
            }
        }
    }

    void reset_map() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = 0;
            }
        }
        player_x = -1;
        player_y = -1;
        enemy_x = -1;
        enemy_y = -1;
    }

    void create_wall(int x, int y) {
        if (x == player_x && y == player_y || x == enemy_x && y == enemy_y) {
            cout << "벽을 생성할 수 없는 지역입니다. (계속 진행하려면 아무키나 입력)" << endl;
            keypress();
            return;
        }
        map[x][y] = 1;
    }

    void create_path(int x, int y) {
        if (x == player_x && y == player_y || x == enemy_x && y == enemy_y) {
            cout << "길을 생성할 수 없는 지역입니다. (계속 진행하려면 아무키나 입력)" << endl;
            keypress();
            return;
        }
        map[x][y] = 0;
    }

    void set_player_position(int x, int y) {
        if (player_x != -1 && player_y != -1) {
            map[player_x][player_y] = 0;
        }
        player_x = x;
        player_y = y;
        map[x][y] = 2;
    }

    void set_enemy_position(int x, int y) {
        if (enemy_x != -1 && enemy_y != -1) {
            map[enemy_x][enemy_y] = 0;
        }
        enemy_x = x;
        enemy_y = y;
        map[x][y] = 3;
    }

    void print() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == player_x && j == player_y) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                    cout << "●";
                }
                else if (i == enemy_x && j == enemy_y) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << "★";
                }
                else if (map[i][j] == 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                    cout << "□";
                }
                else if (map[i][j] == 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
                    cout << "▣";
                }
                else if (map[i][j] == 4) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    cout << "◆";
                }
            }
            cout << endl;
        }
    }

};

class Dijkstra {
private:
    struct Node {
        int x, y, dist;
        bool operator<(const Node& other) const {
            return dist > other.dist;
        }
    };
    Map& map;

public:
    Dijkstra(Map& _map) : map(_map) {}

    void find_shortest_path(int start_x, int start_y, int end_x, int end_y) {
        priority_queue<Node> pq;
        vector<vector<int>> dist(MAXN, vector<int>(MAXN, INF));
        vector<vector<bool>> visited(MAXN, vector<bool>(MAXN, false));
        vector<vector<pair<int, int>>> prev(MAXN, vector<pair<int, int>>(MAXN, make_pair(-1, -1)));

        pq.push({ start_x, start_y, 0 });
        dist[start_x][start_y] = 0;

        while (!pq.empty()) {
            int x = pq.top().x;
            int y = pq.top().y;
            pq.pop();

            if (visited[x][y]) continue;
            visited[x][y] = true;

            // 인접한 노드들 탐색
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    if (dx != 0 && dy != 0) continue;

                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || nx >= MAXN || ny < 0 || ny >= MAXN) continue;
                    if (map.map[nx][ny] == 1 || visited[nx][ny]) continue;

                    int weight = (dx * dy == 0) ? 1 : 141; // 가중치 (대각선 이동인 경우 루트 2에 가까운 값으로 계산)
                    if (dist[nx][ny] > dist[x][y] + weight) {
                        dist[nx][ny] = dist[x][y] + weight;
                        prev[nx][ny] = { x, y };
                        pq.push({ nx, ny, dist[nx][ny] });
                    }
                }
            }
        }

        // 최단 경로 구하기
        int x = end_x, y = end_y;
        if (prev[x][y].first == -1 && prev[x][y].second == -1) {
            cout << "최단경로가 존재하지 않습니다 (계속 진행하려면 아무키나 입력)" << endl;
            keypress();
            return;
        }
        while (x != -1 && y != -1) {
            map.map[x][y] = 4; // 4는 최단 경로에 해당하는 표시
            int px = prev[x][y].first;
            int py = prev[x][y].second;
            x = px;
            y = py;
        }
    }
};

int main() {

    Map map;
    Dijkstra d(map);
    int ans;
    int x;
    int y;
    bool out = true;
    while (out) {
        map.print();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "1. 플레이어 위치 설정" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "2. 적 위치 설정" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        cout << "3. 벽 생성" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "4. 길 생성" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "5. 최단경로 표시" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "6. 맵 초기화" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "7. 종료" << endl;

        cin >> ans;

        switch (ans)
        {
        case 1:
            cout << "좌측상단이 (0,0) 기준으로 오른쪽으로 갈수록 x좌표가 커짐(0~9), 아래쪽으로 갈수록 y좌표가 커짐(0~9)" << endl;
            cout << "x좌표 입력" << endl;
            cin >> x;
            cout << "y좌표 입력" << endl;
            cin >> y;
            map.reset_path();
            map.set_player_position(y, x);
            break;
        case 2:
            cout << "좌측상단이 (0,0)기준으로 오른쪽으로 갈수록 x좌표가 커짐, 아래쪽으로 갈수록 y좌표가 커짐" << endl;
            cout << "x좌표 입력" << endl;
            cin >> x;
            cout << "y좌표 입력" << endl;
            cin >> y;
            map.reset_path();
            map.set_enemy_position(y, x);
            break;
        case 3:
            cout << "좌측상단이 (0,0)기준으로 오른쪽으로 갈수록 x좌표가 커짐, 아래쪽으로 갈수록 y좌표가 커짐" << endl;
            cout << "x좌표 입력" << endl;
            cin >> x;
            cout << "y좌표 입력" << endl;
            cin >> y;
            map.reset_path();
            map.create_wall(y, x);
            break;
        case 4:
            cout << "좌측상단이 (0,0)기준으로 오른쪽으로 갈수록 x좌표가 커짐, 아래쪽으로 갈수록 y좌표가 커짐" << endl;
            cout << "x좌표 입력" << endl;
            cin >> x;
            cout << "y좌표 입력" << endl;
            cin >> y;
            map.reset_path();
            map.create_path(y, x);
            break;
        case 5:
            if (map.player_x != -1 && map.player_y != -1 && map.enemy_x != -1 && map.enemy_y != -1){
                map.reset_path();
                d.find_shortest_path(map.player_x, map.player_y, map.enemy_x, map.enemy_y);
            }
            else {
                cout << "플레이어와 적의 위치를 설정하시오(계속 진행하려면 아무키나 입력)" << endl;
                keypress();
            }
            break;
        case 6:
            map.reset_map();
            break;
        case 7:
            out = false;
            break;
        default:
            break;
        }
        system("cls");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    return 0;
}
