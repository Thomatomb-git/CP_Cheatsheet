// Algoritma Tarjan untuk mencari SCC pada directed graph.
// O(V + E).
const int N = 200005;
vector<int> v[N];
bool vis[N], ins[N];
int disc[N], low[N], gr[N];
stack<int> st;
int id, grid;

void scc(int cur, int par = -1) {
    disc[cur] = low[cur] = ++id;
    vis[cur] = ins[cur] = 1;
    st.push(cur);

    for(int to : v[cur]) {
        if(!vis[to]) {
            scc(to, cur);
            low[cur] = min(low[cur], low[to]);
        } else if(ins[to]) {
            low[cur] = min(low[cur], disc[to]);
        }
    }

    if(low[cur] == disc[cur]) {
        grid++;
        while(true) {
            int u = st.top();
            st.pop();
            gr[u] = grid;
            ins[u] = 0;
            if(u == cur) break;
        }
    }
}
