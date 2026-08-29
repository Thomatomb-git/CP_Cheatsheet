// Algoritma/Fungsi: Pewarnaan sisi greedy (Edge Coloring) pada pohon/hutan sehingga sisi yang bertetangga memiliki warna berbeda.
// Kompleksitas Waktu: O(V + E).
#include <bits/stdc++.h>
using namespace std;

void colorEdges(int ptr, vector<vector<pair<int, int>>>& gra, vector<int>& edgeColors, vector<bool>& isVisited) {
  queue<int> q;
  int c = 0;
  unordered_set<int> colored;
  if (isVisited[ptr]) return;

  isVisited[ptr] = 1;
  for (size_t i = 0; i < gra[ptr].size(); i++) {
    if (edgeColors[gra[ptr][i].second] != -1)
      colored.insert(edgeColors[gra[ptr][i].second]);
  }

  for (size_t i = 0; i < gra[ptr].size(); i++) {
    if (!isVisited[gra[ptr][i].first])
      q.push(gra[ptr][i].first);
    if (edgeColors[gra[ptr][i].second] == -1) {
      while (colored.find(c) != colored.end())
        c++;
      edgeColors[gra[ptr][i].second] = c;
      colored.insert(c);
      c++;
    }
  }
  while (!q.empty()) {
      int temp = q.front();
      q.pop();
      colorEdges(temp, gra, edgeColors, isVisited);
  }
}
