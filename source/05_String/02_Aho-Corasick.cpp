// Algoritma/Fungsi: Aho-Corasick Automaton untuk pencarian banyak pola string sekaligus (multi-pattern matching) dan suffix failure links.
// Kompleksitas Waktu: Konstruksi O(total panjang pola * alfabet), Pencarian Teks O(|T| + matches).
#include <bits/stdc++.h>
using namespace std;

const int K = 26;
struct Vertex {
  int next[K];
  bool leaf = 0;
  int p = -1, ans = 0;
  char pch;
  int link = -1, mlink = -1;
  int go[K];
  Vertex(int p = -1, char ch = '$') : p(p), pch(ch) {
    fill(begin(next), end(next), -1);
    fill(begin(go), end(go), -1);
  }
};

vector<Vertex> t;

void init_aho_corasick() {
    t.clear();
    t.emplace_back();
}

int add_string(string const& s) {
  int v = 0;
  for (char ch : s) {
    int c = ch - 'a';
    if (t[v].next[c] == -1) {
      t[v].next[c] = t.size();
      t.emplace_back(v, ch);
    }
    v = t[v].next[c];
  }
  t[v].leaf = 1;
  return v;
}

int go(int v, char ch);

int get_link(int v) {
  if (t[v].link == -1) {
    if(v == 0 || t[v].p == 0)
      t[v].link = 0;
    else
      t[v].link = go(get_link(t[v].p), t[v].pch);
  }
  return t[v].link;
}

int get_mlink(int v) {
  if (t[v].mlink == -1) {
    if(v == 0 || t[v].p == 0)
      t[v].mlink = 0;
    else {
      int l = get_link(v);
      if(l == 0) t[v].mlink = 0;
      else if(t[l].leaf) t[v].mlink = l;
      else t[v].mlink = get_mlink(l);
    }
  }
  return t[v].mlink;
}

int go(int v, char ch) {
  int c = ch - 'a';
  if (t[v].go[c] == -1) {
    if (t[v].next[c] != -1)
      t[v].go[c] = t[v].next[c];
    else
      t[v].go[c] = (v == 0 ? 0 : go(get_link(v), ch));
  }
  return t[v].go[c];
}
