#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> graph[1001]; // 인접 리스트로 그래프 저장
bool visited[1001]; // 정점 방문 여부를 저장하는 배열

void dfs(int v) {
    visited[v] = true; // v를 방문했다는 표시
    cout << v << " "; // v를 출력
    for (int i = 0; i < graph[v].size(); i++) { // v에 인접한 정점을 방문하며
        int next = graph[v][i]; // 다음에 방문할 정점을 선택
        if (!visited[next]) { // 해당 정점이 방문하지 않은 정점이라면
            dfs(next); // 해당 정점으로 이동하여 dfs 수행
        }
    }
}

void bfs(int v) {
    queue<int> q;
    visited[v] = true; // v를 방문했다는 표시
    q.push(v); // v를 큐에 삽입
    while (!q.empty()) { // 큐가 빌 때까지 반복
        int curr = q.front(); // 큐의 가장 앞에 있는 정점을 선택
        q.pop(); // 선택한 정점을 큐에서 제거
        cout << curr << " "; // 해당 정점을 출력
        for (int i = 0; i < graph[curr].size(); i++) { // 해당 정점에 인접한 정점을 방문하며
            int next = graph[curr][i]; // 다음에 방문할 정점을 선택
            if (!visited[next]) { // 해당 정점이 방문하지 않은 정점이라면
                visited[next] = true; // 해당 정점을 방문했다는 표시
                q.push(next); // 해당 정점을 큐에 삽입
            }
        }
    }
}

int main() {
    int n, m, v;
    cin >> n >> m >> v;

    for (int i = 0; i < m; i++) {
        int u, w;
        cin >> u >> w;
        graph[u].push_back(w); // 양방향 그래프를 인접 리스트로 저장
        graph[w].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end()); // 각 정점마다 인접한 정점 번호를 오름차순으로 정렬
    }

    dfs(v); // DFS 수행
    cout << endl;

    fill(visited, visited + n + 1, false); // 방문 여부 배열 초기화
    bfs(v); // BFS 수행

    return 0;
}
