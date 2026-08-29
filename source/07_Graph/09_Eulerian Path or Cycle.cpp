// Algoritma/Fungsi: Mencari lintasan/siklus Eulerian pada graf tak berarah sederhana dengan mengunjungi setiap sisi tepat satu kali.
// Kompleksitas Waktu: O(E log V) menggunakan std::set.
#include <bits/stdc++.h>
using namespace std;

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
