#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int n, e;
    cout << "Enter number of users and friendships: ";
    cin >> n >> e;
    if (n <= 0 || n > 20 || e < 0) return 1;

    vector<int> adj[20];
    cout << "Enter friendships (user1 user2):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid user ID.\n";
            return 1;
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int user;
    cout << "Enter user ID: ";
    cin >> user;
    if (user < 0 || user >= n) return 1;

    set<int> direct(adj[user].begin(), adj[user].end());
    set<int> fof;
    for (int friendId : direct)
        for (int candidate : adj[friendId])
            if (candidate != user && !direct.count(candidate))
                fof.insert(candidate);

    cout << "Direct friends: ";
    for (int x : direct) cout << x << " ";
    cout << "\nFriends of friends: ";
    for (int x : fof) cout << x << " ";
    cout << '\n';
    return 0;
}
