#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int n, e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;
    if (n <= 0 || n > 20 || e < 0) return 1;

    vector<int> adj[20];
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

    bool visited[20] = {};
    stack<int> st;
    st.push(start);

    cout << "DFS Traversal: ";
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (visited[u]) continue;

        visited[u] = true;
        cout << u << " ";

        // Reverse insertion preserves the usual adjacency order in traversal.
        for (int i = static_cast<int>(adj[u].size()) - 1; i >= 0; i--)
            if (!visited[adj[u][i]]) st.push(adj[u][i]);
    }
    cout << '\n';
    return 0;
}
