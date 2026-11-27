// Monotonic Sliding Window Queue untuk mencari nilai maksimum dalam antrian bergerak secara efisien.
// Amortized O(1) per operasi add dan remove, O(1) untuk getMax().
// NOTE: Pastikan queue tidak kosong sebelum memanggil getMax().
//       Untuk MinQueue, ganti perbandingan < menjadi > pada fungsi add.
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
    assert(!q.empty() && "getMax() called on empty MaxQueue");
    return q.front().first;
  }
};
