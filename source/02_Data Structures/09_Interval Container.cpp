// Interval Container menggunakan set untuk memelihara himpunan interval disjoint (penambahan dan pengurangan interval).
// Amortized O(log N) per operasi penambahan/penghapusan interval.
// NOTE: Interval disimpan sebagai pair [L, R).
//       removeInterval meng-erase lalu re-insert, bukan cast-away constness (UB).
typedef pair<int, int> pii;

set<pii>::iterator addInterval(set<pii> &is, int L, int R){
  if (L == R) return is.end();
  auto it = is.lower_bound({L,R}), before = it;
  while (it != is.end() && it->first <= R){
    R = max(R, it->second);
    before = it = is.erase(it);
  }
  if (it != is.begin() && (--it)->second >= L){
    L = min(L, it->first);
    R = max(R, it->second);
    is.erase(it);
  }
  return is.insert(before, {L, R});
}

void removeInterval(set<pii> &is, int L, int R){
  if(L == R) return;
  auto it = addInterval(is, L, R);
  auto r2 = it->second;
  int oldL = it->first;
  is.erase(it);
  if (oldL != L) is.emplace(oldL, L);
  if (R != r2) is.emplace(R, r2);
}
