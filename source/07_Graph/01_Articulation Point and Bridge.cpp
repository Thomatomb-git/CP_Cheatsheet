// Algoritma/Fungsi: Algoritma Tarjan DFS untuk mencari Titik Artikulasi (Cut Vertices) dan Jembatan (Bridges) pada graf tak berarah/multigraf.
// Kompleksitas Waktu: O(V + E).
#include <bits/stdc++.h>
using namespace std;

struct GraphBridges {
    int n, timer;
    vector<vector<pair<int, int>>> gr;
    vector<int> vis, low;
    vector<pair<int, int>> bridges;
    vector<int> articulation_points;

    GraphBridges(int _n) : n(_n), timer(0), gr(_n + 1), vis(_n + 1, -1), low(_n + 1, -1) {}

    void add_edge(int u, int v, int edge_id) {
        gr[u].push_back({v, edge_id});
        gr[v].push_back({u, edge_id});
    }

    void dfs(int u, int p_edge = -1) {
        vis[u] = low[u] = timer++;
        int kids = 0;
        bool is_art = false;

        for(auto& edge : gr[u]) {
            int v = edge.first, id = edge.second;
            if(id == p_edge) continue;
            if(vis[v] >= 0) {
                low[u] = min(low[u], vis[v]);
            } else {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if(low[v] > vis[u])
                    bridges.push_back({u, v});
                if(low[v] >= vis[u] && p_edge != -1)
                    is_art = true;
                ++kids;
            }
        }
        if(p_edge == -1 && kids > 1)
            is_art = true;
        if(is_art)
            articulation_points.push_back(u);
    }
};
