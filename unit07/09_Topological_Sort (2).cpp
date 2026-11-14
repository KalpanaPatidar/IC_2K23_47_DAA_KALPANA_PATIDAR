#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, e;
    cout << "Enter number of vertices and directed edges: ";
    cin >> n >> e;
    if (n <= 0 || n > 20 || e < 0) return 1;

    vector<int> adj[20];
    int indegree[20] = {};

    cout << "Enter directed edges (u v) meaning u -> v:\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid vertex.\n";
            return 1;
        }
        adj[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (--indegree[v] == 0) q.push(v);
    }

    if (static_cast<int>(order.size()) != n) {
        cout << "Cycle detected. Topological ordering is not possible.\n";
    } else {
        cout << "Topological Order: ";
        for (int v : order) cout << v << " ";
        cout << '\n';
    }
    return 0;
}
