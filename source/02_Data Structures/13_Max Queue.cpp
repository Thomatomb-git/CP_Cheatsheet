// Algoritma/Fungsi: Monotonic Sliding Window Queue untuk mencari nilai maksimum dalam antrian bergerak secara efisien.
// Kompleksitas Waktu: Amortized O(1) per operasi add dan remove, O(1) untuk getMax().
#include <bits/stdc++.h>
using namespace std;

struct MaxQueue{
  deque<pair<int,int>> q;
  int cntAdd, cntRem;

  MaxQueue() : cntAdd(0), cntRem(0) {};

  void add(int x){
    while(!q.empty()&&q.back().first<x)q.pop_back();
    q.push_back({x,cntAdd++});
  }
  void remove(){
    if (!q.empty() && q.front().second == cntRem)
      q.pop_front();
    cntRem++;
  }
  int getMax(){
    return q.front().first;
  }
};
