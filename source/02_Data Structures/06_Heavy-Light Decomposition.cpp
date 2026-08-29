// Algoritma/Fungsi: Heavy-Light Decomposition (HLD) pada Tree 1-based index untuk path update, path query, dan subtree update/query.
// Kompleksitas Waktu: Path Query/Update O(log^2 N), Subtree Query/Update O(log N).
#include <bits/stdc++.h>
using namespace std;

struct Segtree {
    int n;
    vector<int> t;
    void init(int sz) { n = sz; t.assign(4 * n, 0); }
    void update(int l, int r, int x) { /* custom update */ }
    int query(int l, int r) { return 0; /* custom query */ }
};

class HLD {
private:
    vector<vector<int>> adj;
    vector<int> sz, in, out, nxt, par, depth;
    Segtree DS;
    int timer = -1;

    void dfs_sz(int u, int p = 0, int d = 0) {
        sz[u] = 1;
        par[u] = p;
        depth[u] = d;
        for(auto &v : adj[u]) {
            if(v != p) {
                dfs_sz(v, u, d + 1);
                sz[u] += sz[v];
            }
        }
        for(auto &v : adj[u]) {
            if(v != p && (adj[u][0] == p || sz[v] > sz[adj[u][0]])) {
                swap(v, adj[u][0]);
            }
        }
    }

    void dfs_hld(int u, int p = 0) {
        in[u] = ++timer;
        for(auto &v : adj[u]) {
            if(v != p) {
                nxt[v] = (v == adj[u][0] ? nxt[u] : v);
                dfs_hld(v, u);
            }
        }
        out[u] = timer;
    }

public:
    HLD(int n) {
        adj.assign(n + 1, vector<int>());
        sz.assign(n + 1, 0);
        in.resize(n + 1);
        out.resize(n + 1);
        nxt.assign(n + 1, 0);
        par.assign(n + 1, 0);
        depth.assign(n + 1, 0);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(int root = 1) {
        dfs_sz(root, 0, 0);
        nxt[root] = root;
        dfs_hld(root, 0);
        DS.init(timer + 1);
    }

    void update_path(int u, int v, int x) {
        for(; nxt[u] != nxt[v]; v = par[nxt[v]]) {
            if(depth[nxt[u]] > depth[nxt[v]]) swap(u, v);
            DS.update(in[nxt[v]], in[v], x);
        }
        if(depth[u] > depth[v]) swap(u, v);
        DS.update(in[u], in[v], x);
    }

    int query_path(int u, int v) {
        int ans = 0;
        for(; nxt[u] != nxt[v]; v = par[nxt[v]]) {
            if(depth[nxt[u]] > depth[nxt[v]]) swap(u, v);
            ans = max(ans, DS.query(in[nxt[v]], in[v]));
        }
        if(depth[u] > depth[v]) swap(u, v);
        ans = max(ans, DS.query(in[u], in[v]));
        return ans;
    }

    void update_subtree(int u, int x) {
        DS.update(in[u], out[u], x);
    }

    int query_subtree(int u) {
        return DS.query(in[u], out[u]);
    }
};
