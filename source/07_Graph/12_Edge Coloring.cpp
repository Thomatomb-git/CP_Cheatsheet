void colorEdges(int ptr, vector<vector<pair<int, int>>>& gra, vector<int>& edgeColors, bool isVisited[])
{
  queue<int> q;
  int c = 0;
  unordered_set<int> colored;
  if (isVisited[ptr]) return;

  isVisited[ptr] = 1;
  for (int i = 0; i < gra[ptr].size(); i++) {
    if (edgeColors[gra[ptr][i].second] != -1)
      colored.insert(edgeColors[gra[ptr][i].second]);
  }

  for (int i = 0; i < gra[ptr].size(); i++) {
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