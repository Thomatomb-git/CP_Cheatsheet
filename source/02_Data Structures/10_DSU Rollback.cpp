// DSU dengan riwayat perubahan untuk mendukung operasi rollback/undo.
// Find/Join O(log N), Rollback O(1) per operasi yang di-undo.
#define fi first
#define se second
typedef vector<int> vi;
typedef pair<int, int> pii;

struct RollbackUF{
  vi e;
  vector<pii> st;
  RollbackUF(int n) : e(n, -1){}
  int size (int x){
    return -e[find(x)];
  }
  int find(int x){
    return (e[x] < 0) ? x : find(e[x]);
  }
  int time(){
    return st.size();
  }
  void rollback(int t){
    for (int i = time(); i-->t; )
      e[st[i].fi] = st[i].se;
    st.resize(t);
  }
  bool join(int a, int b){
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.push_back({a, e[a]});
    st.push_back({b, e[b]});
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};
