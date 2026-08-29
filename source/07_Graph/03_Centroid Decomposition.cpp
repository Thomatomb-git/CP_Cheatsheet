// Algoritma/Fungsi: Centroid Decomposition pada Tree untuk teknik divide and conquer jalur/lintasan pada pohon.
// Kompleksitas Waktu: Pembentukan dekomposisi O(N log N), kedalaman pohon centroid O(log N).
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> adj[N];
int sz[N], par_cen[N];
bool rem[N];

void get_sz(int u, int p = 0) {
    sz[u] = 1;
    for(int v : adj[u]) {
        if(v != p && !rem[v]) {
            get_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

int get_centroid(int u, int p, int total_sz) {
    for(int v : adj[u]) {
        if(v != p && !rem[v] && sz[v] > total_sz / 2)
            return get_centroid(v, u, total_sz);
    }
    return u;
}

int build_cen(int u) {
    get_sz(u, 0);
    int cen = get_centroid(u, 0, sz[u]);
    rem[cen] = true;

    for(int v : adj[cen]) {
        if(!rem[v]) {
            int sub_cen = build_cen(v);
            par_cen[sub_cen] = cen;
        }
    }
    return cen;
}
