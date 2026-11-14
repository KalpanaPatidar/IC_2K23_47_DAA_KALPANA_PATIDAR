#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    if (n <= 0 || n > 20 || e < 0) {
        cout << "Invalid graph size.\n";
        return 1;
    }

    vector<int> adj[20];
    cout << "Enter edges (u v), using vertices 0 to " << n - 1 << ":\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid vertex.\n";
            return 1;
        }
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        cout << i << " -> ";
        for (int v : adj[i]) cout << v << " ";
        cout << '\n';
    }
    return 0;
}
