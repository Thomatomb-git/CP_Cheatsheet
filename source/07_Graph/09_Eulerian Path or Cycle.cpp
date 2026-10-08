// Mencari lintasan/siklus Eulerian pada graf tak berarah sederhana dengan mengunjungi setiap sisi tepat satu kali.
// O(E log V) menggunakan set.
vector<set<int>> g;
vector<int> ans;

void dfs(int u) {
  while(g[u].size()) {
    int v = *g[u].begin();
    g[u].erase(v);
    g[v].erase(u);
    dfs(v);
  }
  ans.push_back(u);
}
