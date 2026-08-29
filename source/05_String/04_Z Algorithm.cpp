// Algoritma/Fungsi: Z-Algorithm menghitung array Z di mana Z[i] adalah panjang prefix terpanjang dari S yang cocok dengan S[i...|S|-1].
// Kompleksitas Waktu: O(N) linier.
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vi Z(const string &S){
  vi z(S.size());
  int l = -1, r = -1;
  for (int i = 1; i < (int)S.size(); i++){
    z[i] = i >= r ? 0 : min(r-i, z[i-l]);
    while(i + z[i] < (int)S.size() && S[i+z[i]] == S[z[i]])
      z[i]++;
    if (i + z[i] > r) l = i, r = i+z[i];
  }
  return z;
}
