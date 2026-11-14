#include <iostream>
using namespace std;

int main() {
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;

    if (n <= 0 || n > 20) {
        cout << "Vertices must be between 1 and 20.\n";
        return 1;
    }

    int adj[20][20] = {};

    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter edges (u v), using vertices 0 to " << n - 1 << ":\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid vertex.\n";
            return 1;
        }
        adj[u][v] = adj[v][u] = 1; // Undirected graph
    }

    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << adj[i][j] << " ";
        cout << '\n';
    }
    return 0;
}
