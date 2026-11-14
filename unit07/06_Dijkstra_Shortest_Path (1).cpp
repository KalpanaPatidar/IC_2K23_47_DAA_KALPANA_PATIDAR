#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;
    if (n <= 0 || n > 20 || e < 0) return 1;

    vector<pair<int, int>> adj[20];
    cout << "Enter undirected weighted edges (u v weight):\n";
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u < 0 || u >= n || v < 0 || v >= n || w < 0) {
            cout << "Invalid edge or negative weight. Dijkstra needs non-negative weights.\n";
            return 1;
        }
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;
    if (source < 0 || source >= n) return 1;

    const long long INF = LLONG_MAX / 4;
    vector<long long> dist(n, INF);
    vector<bool> used(n, false);
    dist[source] = 0;

    for (int step = 0; step < n; step++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!used[i] && (u == -1 || dist[i] < dist[u])) u = i;

        if (u == -1 || dist[u] == INF) break;
        used[u] = true;

        for (auto edge : adj[u]) {
            int v = edge.first, w = edge.second;
            if (!used[v] && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    cout << "Shortest distances from " << source << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "To " << i << " = ";
        if (dist[i] == INF) cout << "Unreachable\n";
        else cout << dist[i] << '\n';
    }
    return 0;
}
