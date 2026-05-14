// graph 1-based index
class HLD{
private:
    vector<vector<int>> adj;
    vector<int> sz, in, out, nxt, par;
    Segtree DS;
    int timer = -1;

    void dfs (int u, int p){
        sz[u] = 1;
        par[u] = p;
        for (auto &v : adj[u])
            if (v != p){
                dfs(v, u);
                sz[u] += sz[v];
                if (sz[v] >= sz[adj[u][0]])
                    swap(v, adj[u][0]);
            }
    }
    void chain(int u, int p){
        if(p == u) 
            nxt[u] = u;
        in[u] = ++timer;
        for (auto &v : adj[u])
            if(v != p){
                nxt[v] = (v == adj[u][0] ? nxt[u] : v);
                chain(v, u);
            }
        out[u] = timer;
    }

public:
    HLD(int n){
        adj.assign(n+1, vector<int>());
        sz.assign(n+1, 0);
        in.resize(n+1);
        out.resize(n+1);
        nxt.assign(n+1, 0);
        par.assign(n+1, -1);
    }
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void update_path(int u, int v, int x){
        for(; in[nxt[u]] != in[nxt[v]]; v = par[nxt[v]]){
            if(in[u] > in[v]) swap(u, v);
            DS.update(in[nxt[v]], in[v], x);
        }
        if(in[u] > in[v]) swap(u, v);
        DS.update(in[u], in[v], x);
    }
    int query_path(int u, int v){
        int ans = -1;
        for(; in[nxt[u]] != in[nxt[v]]; v = par[nxt[v]]){
            if(in[u] > in[v]) swap(u, v);
            ans = max(ans,DS.query(in[nxt[v]], in[v]));
        }
        if (in[u] > in[v]) swap(u, v);
        ans = max(ans, DS.query(in[u], in[v]));
        return ans;
    }
    void update_subtree(int u, int x){
        DS.update(in[u], out[u], x);
    }
    int query_subtree(int u){
        return DS.query(in[u], out[u]);
    }
    void init(){
        dfs(1, 1);
        chain(1, 1);
        DS.init(timer + 1);
    }
};