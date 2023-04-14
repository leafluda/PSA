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
    int map[10][10]; // 10 x 10 크기의 맵 배열
    int player_x, player_y; // 플레이어의 좌표
    int enemy_x, enemy_y; // 적의 좌표

public:
    Map() { // 생성자
        for (int i = 0; i < 10; i++) { // 맵 초기화
            for (int j = 0; j < 10; j++) {
                map[i][j] = 0;
            }
        }
        player_x = -1; // 플레이어 초기 위치
        player_y = -1;
        enemy_x = -1; // 적 초기 위치
        enemy_y = -1;
    }

    void reset_path() { // 최단 경로 초기화 함수
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (map[i][j] == 4) { // 최단 경로 표시가 된 부분만 초기화
                    map[i][j] = 0;
                }
            }
        }
    }

    void reset_map() { // 맵 전체 초기화 함수
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = 0; // 맵 초기화
            }
        }
        player_x = -1; // 플레이어, 적 위치 초기화
        player_y = -1;
        enemy_x = -1;
        enemy_y = -1;
    }

    void create_wall(int x, int y) { // 벽 생성 함수
        if (x < 0 || x > 9 || y < 0 || y > 9) { // 맵을 벗어난 좌표를 입력할경우
            cout << "맵 좌표를 벗어났습니다. (계속 진행하려면 아무키나 입력)" << endl; // 오류 메시지 출력
            keypress(); // 키 입력 대기
            return;
        }
        if (x == player_x && y == player_y || x == enemy_x && y == enemy_y) { // 벽 생성 지점에 플레이어나 적이 위치할 경우
            cout << "벽을 생성할 수 없는 지역입니다. (계속 진행하려면 아무키나 입력)" << endl; // 오류 메시지 출력
            keypress(); // 키 입력 대기
            return;
        }
        map[x][y] = 1; // 벽 표시
    }

    void create_path(int x, int y) { // 길 생성 함수
        if (x < 0 || x > 9 || y < 0 || y > 9) { // 맵을 벗어난 좌표를 입력할경우
            cout << "맵 좌표를 벗어났습니다. (계속 진행하려면 아무키나 입력)" << endl; // 오류 메시지 출력
            keypress(); // 키 입력 대기
            return;
        }
        if (x == player_x && y == player_y || x == enemy_x && y == enemy_y) { // 길 생성 지점에 플레이어나 적이 위치할 경우
            cout << "길을 생성할 수 없는 지역입니다. (계속 진행하려면 아무키나 입력)" << endl; // 오류 메시지 출력
            keypress(); // 키 입력 대기
            return;
        }
        map[x][y] = 0; // 길 표시
    }

    void set_player_position(int x, int y) { // 플레이어 위치 설정 함수
        if (x < 0 || x > 9 || y < 0 || y > 9) { // 맵을 벗어난 좌표를 입력할경우
            cout << "맵 좌표를 벗어났습니다. (계속 진행하려면 아무키나 입력)" << endl; // 오류 메시지 출력
            keypress(); // 키 입력 대기
            return;
        }
        if (player_x != -1 && player_y != -1) { // 이미 플레이어가 위치한 경우
            map[player_x][player_y] = 0; // 이전 위치 초기화
        }
        player_x = x;
        player_y = y;
        map[x][y] = 2; // 맵 배열에 플레이어의 위치 표시
    }

    void set_enemy_position(int x, int y) {
        if (x < 0 || x > 9 || y < 0 || y > 9) { // 맵을 벗어난 좌표를 입력할경우
            cout << "맵 좌표를 벗어났습니다. (계속 진행하려면 아무키나 입력)" << endl; // 오류 메시지 출력
            keypress(); // 키 입력 대기
            return;
        }
        if (enemy_x != -1 && enemy_y != -1) { // 이전 적의 위치가 있을 경우
            map[enemy_x][enemy_y] = 0; // 맵 배열에서 이전 적의 위치 삭제
        }
        enemy_x = x;
        enemy_y = y;
        map[x][y] = 3; // 맵 배열에 적의 위치 표시
    }

    void print() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) { 
                if (i == player_x && j == player_y) { // 현재 위치가 플레이어의 위치일 경우
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // 글자색 변경
                    cout << "●"; // 플레이어를 나타내는 기호 출력
                }
                else if (i == enemy_x && j == enemy_y) { // 현재 위치가 적의 위치일 경우
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // 글자색 변경
                    cout << "★"; // 적을 나타내는 기호 출력
                }
                else if (map[i][j] == 0) { // 해당 위치에 아무것도 없을 경우
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); // 글자색 변경
                    cout << "□"; // 길을 나타내는 기호 출력
                }
                else if (map[i][j] == 1) { // 해당 위치에 벽이 있을 경우
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); // 글자색 변경
                    cout << "▣"; // 벽을 나타내는 기호 출력
                }
                else if (map[i][j] == 4) { // 해당 위치에 경로가 있을 경우
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // 글자색 변경
                    cout << "◆"; // 경로를 나타내는 기호 출력
                }
            }
            cout << endl; 
        }
    }

};

// Dijkstra 클래스 정의
class Dijkstra {
private:
    // 노드 구조체 정의
    struct Node {
        int x, y, dist;
        // 노드간의 우선순위 비교 연산자 오버로딩
        bool operator<(const Node& other) const {
            return dist > other.dist;
        }
    };
    Map& map; // 맵 객체

public:
    // 생성자
    Dijkstra(Map& _map) : map(_map) {}

    // 시작점과 끝점을 입력받아 최단경로를 찾는 함수
    void find_shortest_path(int start_x, int start_y, int end_x, int end_y) {
        // 우선순위 큐, 거리배열, 방문여부배열, 이전노드배열 초기화
        priority_queue<Node> pq;
        vector<vector<int>> dist(MAXN, vector<int>(MAXN, INF));
        vector<vector<bool>> visited(MAXN, vector<bool>(MAXN, false));
        vector<vector<pair<int, int>>> prev(MAXN, vector<pair<int, int>>(MAXN, make_pair(-1, -1)));

        // 시작점 추가
        pq.push({ start_x, start_y, 0 });
        dist[start_x][start_y] = 0;

        // 다익스트라 알고리즘 실행
        while (!pq.empty()) {
            int x = pq.top().x;
            int y = pq.top().y;
            pq.pop();

            // 이미 방문한 노드인 경우 스킵
            if (visited[x][y]) continue;
            visited[x][y] = true;

            // 인접한 노드들 탐색
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    // 대각선 방향은 스킵
                    if (dx == 0 && dy == 0) continue;
                    if (dx != 0 && dy != 0) continue;

                    // 인접노드의 위치 계산
                    int nx = x + dx;
                    int ny = y + dy;
                    // 인접노드가 맵 범위를 벗어나는 경우 스킵
                    if (nx < 0 || nx >= MAXN || ny < 0 || ny >= MAXN) continue;
                    // 인접노드가 벽이거나 이미 방문한 노드인 경우 스킵
                    if (map.map[nx][ny] == 1 || visited[nx][ny]) continue;

                    // 가중치 계산 (대각선인 경우 루트 2에 가까운 값으로 계산)
                    int weight = (dx * dy == 0) ? 1 : 141;
                    // 이전 노드까지의 거리와 가중치를 더한 값이 현재 노드까지의 거리보다 작은 경우 최신화
                    if (dist[nx][ny] > dist[x][y] + weight) {
                        dist[nx][ny] = dist[x][y] + weight;
                        prev[nx][ny] = { x, y };
                        // nx, ny 위치에서 이전 위치로 x, y를 저장함. (최단 경로 역추적을 위해)
                        pq.push({ nx, ny, dist[nx][ny] });
                        // 현재 위치에서 nx, ny로 이동하는데 드는 비용(dist[nx][ny])을 우선순위 큐에 저장함
                    }
                }
            }
        }

        // 최단 경로 구하기
        int x = end_x, y = end_y;
        // 목표지점의 좌표를 x, y에 저장
        if (prev[x][y].first == -1 && prev[x][y].second == -1) {
            cout << "최단경로가 존재하지 않습니다. (계속 진행하려면 아무키나 입력)" << endl;
            keypress();
            return;
        }
        // 최단경로가 존재하지 않을 경우 메시지를 출력하고 함수를 종료
        while (x != -1 && y != -1) {
            map.map[x][y] = 4; // 4는 최단 경로에 해당하는 표시
            int px = prev[x][y].first;
            int py = prev[x][y].second;
            x = px;
            y = py;
        }
        // 최단 경로를 역추적하면서 해당 경로를 4로 표시함. 이전 위치로 이동하기 위한 x, y를 px, py에 저장하고 x, y를 갱신함.
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
            cout << "좌측상단이 (0,0) 기준으로 오른쪽으로 갈수록 x좌표가 커짐(0~9), 아래쪽으로 갈수록 y좌표가 커짐(0~9)." << endl;
            cout << "x좌표 입력" << endl;
            cin >> x;
            cout << "y좌표 입력" << endl;
            cin >> y;
            map.reset_path();
            map.set_player_position(y, x);
            break;
        case 2:
            cout << "좌측상단이 (0,0)기준으로 오른쪽으로 갈수록 x좌표가 커짐(0~9), 아래쪽으로 갈수록 y좌표가 커짐(0~9)." << endl;
            cout << "x좌표 입력" << endl;
            cin >> x;
            cout << "y좌표 입력" << endl;
            cin >> y;
            map.reset_path();
            map.set_enemy_position(y, x);
            break;
        case 3:
            cout << "좌측상단이 (0,0)기준으로 오른쪽으로 갈수록 x좌표가 커짐(0~9), 아래쪽으로 갈수록 y좌표가 커짐(0~9)." << endl;
            cout << "x좌표 입력" << endl;
            cin >> x;
            cout << "y좌표 입력" << endl;
            cin >> y;
            map.reset_path();
            map.create_wall(y, x);
            break;
        case 4:
            cout << "좌측상단이 (0,0)기준으로 오른쪽으로 갈수록 x좌표가 커짐(0~9), 아래쪽으로 갈수록 y좌표가 커짐(0~9)" << endl;
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
                cout << "플레이어와 적의 위치를 설정하시오.(계속 진행하려면 아무키나 입력)" << endl;
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
