// Algoritma/Fungsi: Menemukan panjang lintasan terpendek ke-k dari simpul s ke t pada graf berbobot positif menggunakan Priority Queue (Dijkstra-based).
// Kompleksitas Waktu: O(K * E log(K * V)).
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
vector<pair<int, int>> g[MAXN];
int vis_cnt[MAXN];

int kth_shortest_path(int s, int t, int k, int n) {
    fill(vis_cnt, vis_cnt + n + 1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});

    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if(vis_cnt[u] >= k) continue;
        vis_cnt[u]++;

        if(u == t && vis_cnt[t] == k)
            return d;

        for(auto& edge : g[u]) {
            int v = edge.first, w = edge.second;
            if(vis_cnt[v] < k)
                pq.push({d + w, v});
        }
    }
    return -1;
}
