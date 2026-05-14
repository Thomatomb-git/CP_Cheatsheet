#define NMAX
vector<int> v[N];
bool vis[N], ins[N];
int disc[N], low[N], gr[N];
stack<int> st;
int id, grid;
void scc(int cur, int par){
  disc[cur] = low[cur] = ++id;
  vis[cur] = ins[cur] = 1;
  st.push(cur);
  for(int to : v[cur]){
    //if(to==par)continue;//iniuntukSO(sccundirected)
    if (!vis[to]) 
      scc(to, cur);
    if (ins[to])
      low[cur]= min(low[cur], low[to]);
  }
  if (low[cur] == disc[cur]){
    grid++; //groupid
    while (ins[cur]){
      gr[st.top()] = grid;
      ins[st.top()] = 0;
      st.pop();
    }
  }
}