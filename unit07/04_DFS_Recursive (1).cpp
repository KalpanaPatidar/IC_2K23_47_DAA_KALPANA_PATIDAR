#include <iostream>
#include <vector>
using namespace std;

vector<int> adj[20];
bool visited[20] = {};

void dfs(int u) {
    visited[u] = true;
    cout << u << " ";
    for (int v : adj[u])
        if (!visited[v]) dfs(v);
}

int main() {
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;
    if (n <= 0 || n > 20 || e < 0) return 1;

    cout << "Enter undirected edges (u v):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid vertex.\n";
            return 1;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;
    if (start < 0 || start >= n) return 1;

    cout << "DFS Traversal: ";
    dfs(start);
    cout << '\n';
    return 0;
}
