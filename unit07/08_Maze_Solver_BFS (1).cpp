#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    const int R = 5, C = 5;
    int maze[R][C] = {
        {0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    // 0 = open cell, 1 = wall. Start = (0,0), destination = (4,4).
    pair<int,int> parent[R][C];
    bool visited[R][C] = {};
    queue<pair<int,int>> q;
    int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

    if (maze[0][0] == 1 || maze[R-1][C-1] == 1) {
        cout << "Start or destination is blocked.\n";
        return 0;
    }

    q.push({0, 0});
    visited[0][0] = true;
    parent[0][0] = {-1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x == R-1 && y == C-1) break;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < R && ny >= 0 && ny < C &&
                maze[nx][ny] == 0 && !visited[nx][ny]) {
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }

    if (!visited[R-1][C-1]) {
        cout << "No path found.\n";
        return 0;
    }

    vector<pair<int,int>> path;
    for (pair<int,int> cur = {R-1, C-1}; cur.first != -1;
         cur = parent[cur.first][cur.second])
        path.push_back(cur);
    reverse(path.begin(), path.end());

    cout << "Shortest path (row, column):\n";
    for (auto cell : path)
        cout << "(" << cell.first << "," << cell.second << ") ";
    cout << "\nNumber of moves: " << path.size() - 1 << '\n';
    return 0;
}
