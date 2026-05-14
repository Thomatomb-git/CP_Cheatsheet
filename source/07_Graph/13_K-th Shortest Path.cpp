// k = shortest path ke berapa.
// n = jumlah vertex.
// solve(i,j): shortest path dari i ke j.
const int MAXN = 100;
const int MAXK = 40;
vector<pair<int,int>> g[MAXN];
priority_queue<pair<int,int>> pq;
int visit[MAXN], n, k;
int solve(int s, int t){
  FILL(visit, 0);
  pq.push(mp(0, s));
  int ret = 0;
  while (!pq.empty()){ 
    int awal = -pq.top().first, f = pq.top().second;
    pq.pop();
    if (visit[f] >= k) continue;
    visit[f]++;
    if (f == t) ret += awal;
    for (auto x : g[f]) if (visit[x.first] < k)
      pq.push(mp(-(awal + x.se), x.first));
  }
  return ret;
}
int inside_main(){
  k = GI;
  n = GI;
  for (int nedge = 0; nedge < GI; nedge++){
    int a = GI-1, b = GI-1, c = GI;
    g[a].pb(mp(b,c));
    g[b].pb(mp(a,c));
  }
  printf("%d\n",solve(0,n-1));
}