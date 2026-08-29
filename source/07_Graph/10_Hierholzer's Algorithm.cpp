// Algoritma/Fungsi: Algoritma Hierholzer untuk mencari lintasan atau siklus Eulerian pada graf berarah.
// Kompleksitas Waktu: O(V + E).
#include <bits/stdc++.h>
using namespace std;

vector<int> hierholzer(int start_node, vector<vector<int>>& adj) {
    stack<int> path;
    vector<int> euler;
    path.push(start_node);
    int cur = start_node;

    while(!path.empty()) {
        if(!adj[cur].empty()) {
            path.push(cur);
            int nxt = adj[cur].back();
            adj[cur].pop_back();
            cur = nxt;
        } else {
            euler.push_back(cur);
            cur = path.top();
            path.pop();
        }
    }
    reverse(euler.begin(), euler.end());
    return euler;
}
