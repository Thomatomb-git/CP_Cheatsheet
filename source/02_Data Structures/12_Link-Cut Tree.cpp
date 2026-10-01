// Link-Cut Tree (LCT) berbasis Splay Tree untuk konektivitas dinamis graf pohon, query path, dan pemeliharaan subtree.
// Amortized O(log N) per operasi link, cut, makeRoot, dan path query.
typedef long long ll;
const int maxV = 100005;

typedef struct Node* Np;
struct Node {
  Np p, c[2];
  bool flip = 0;
  int vtx;
  ll val, sz;
  int sub, vsub = 0;
  ll stsum;

  Node(int _vtx, int _val = 1) : vtx(_vtx), val(_val) {
    p = c[0] = c[1] = nullptr;
    calc();
  }

  friend int getSz(Np x) { return x ? x->sz : 0; }
  friend int getSub(Np x) { return x ? x->sub : 0; }
  friend ll getStSum(Np x) { return x ? x->stsum : 0; }

  void prop() {
    if(!flip) return;
    swap(c[0], c[1]);
    flip = 0;
    for(int i = 0; i < 2; i++) {
      if(c[i]) c[i]->flip ^= 1;
    }
  }

  void calc() {
    for(int i = 0; i < 2; i++) {
      if(c[i]) c[i]->prop();
    }
    sz = 1 + getSz(c[0]) + getSz(c[1]);
    sub = 1 + getSub(c[0]) + getSub(c[1]) + vsub;
    stsum = val + getStSum(c[0]) + getStSum(c[1]);
  }

  int dir() {
    if(!p) return -2;
    for(int i = 0; i < 2; i++) {
      if(p->c[i] == this) return i;
    }
    return -1;
  }

  bool isRoot() { return dir() < 0; }

  friend void setLink(Np x, Np y, int d) {
    if(y) y->p = x;
    if(d >= 0) x->c[d] = y;
  }

  void rot() {
    assert(!isRoot());
    int x = dir();
    Np pa = p;
    setLink(pa->p, this, pa->dir());
    setLink(pa, c[x ^ 1], x);
    setLink(this, pa, x ^ 1);
    pa->calc();
  }

  void splay() {
    while(!isRoot() && !p->isRoot()) {
      p->p->prop(), p->prop(), prop();
      dir() == p->dir() ? p->rot() : rot();
      rot();
    }
    if(!isRoot()) p->prop(), prop(), rot();
    prop();
    calc();
  }

  Np fbo(int b) {
    prop();
    int z = getSz(c[0]);
    if(b == z) {
      splay();
      return this;
    }
    return b < z ? c[0]->fbo(b) : c[1]->fbo(b - z - 1);
  }

  void access() {
    for(Np v = this, pre = nullptr; v; v = v->p) {
      v->splay();
      if(pre) v->vsub -= pre->sub;
      if(v->c[1]) v->vsub += v->c[1]->sub;
      v->c[1] = pre;
      v->calc();
      pre = v;
    }
    splay();
    assert(!c[1]);
  }

  void makeRoot() {
    access();
    flip ^= 1;
    access();
    assert(!c[0] && !c[1]);
  }

  friend Np lca(Np x, Np y) {
    if(x == y) return x;
    x->access(), y->access();
    if(!x->p) return nullptr;
    x->splay();
    return x->p ? x->p : x;
  }

  friend bool connected(Np x, Np y) { return lca(x, y) != nullptr; }

  int distRoot() {
    access();
    return getSz(c[0]);
  }

  Np getRoot() {
    access();
    Np a = this;
    while(a->c[0]) a = a->c[0], a->prop();
    a->access();
    return a;
  }

  Np getPar(int b) {
    access();
    b = getSz(c[0]) - b;
    assert(b >= 0);
    return fbo(b);
  }

  void setVal(int v) { access(); val = v; calc(); }
  void addVal(int v) { access(); val += v; calc(); }

  friend void link(Np x, Np y, bool force = 1) {
    assert(!connected(x, y));
    if(force) {
      y->makeRoot();
    } else {
      y->access();
      assert(!y->c[0]);
    }
    x->access();
    setLink(y, x, 0);
    y->calc();
  }

  friend void cut(Np y) {
    y->access();
    assert(y->c[0]);
    y->c[0]->p = NULL;
    y->c[0] = NULL;
    y->calc();
  }

  friend void cut(Np x, Np y) {
    x->makeRoot();
    y->access();
    assert(y->c[0] == x && !x->c[0] && !x->c[1]);
    cut(y);
  }
};
Np LCT[maxV];
