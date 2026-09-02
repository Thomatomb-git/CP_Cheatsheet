// Algoritma/Fungsi: Double Polynomial Rolling Hash untuk menghitung dan membandingkan hash substring dalam O(1).
// Kompleksitas Waktu: Prekomputasi O(N), Query getHash O(1).
// NOTE: Base (key) bersifat static, di-generate sekali saja. Semua instance hashing berbagi
//       base yang sama sehingga hash bisa dibandingkan antar string berbeda.
//       Gunakan double hash (2 moduli) untuk mengurangi collision probability.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rng_hash(chrono::steady_clock::now().time_since_epoch().count());

class hashing{
public:
  int n;
  string s;
  static constexpr int mod[2] = {1000000007, 1000000009};
  static vector<ll> key[2];
  static bool key_initialized;
  vector<pair<ll,ll>> hsh;

  static void init_keys(int sz) {
    if(key_initialized && (int)key[0].size() >= sz + 1) return;
    for(int i = 0; i < 2; i++){
      key[i].resize(sz + 1);
      if(!key_initialized) {
        key[i][0] = 1;
        do {
          key[i][1] = 257 + (rng_hash() % (mod[i] - 300));
        } while(key[i][1] <= 256);
      }
      int start = key_initialized ? (int)key[i].size() : 2;
      key[i].resize(sz + 1);
      for (int j = start; j <= sz; j++){
        key[i][j] = 1LL * key[i][j-1] * key[i][1] % mod[i];
      }
    }
    key_initialized = true;
  }

  hashing(string _s) : s(_s){
    n = (int) s.size();
    if(n == 0) return;
    init_keys(n);
    hsh.resize(n);
    hsh[0] = {s[0], s[0]};
    for (int i = 1; i < n; i++){
      hsh[i].first = (1LL * hsh[i-1].first * key[0][1] % mod[0] + s[i]) % mod[0];
      hsh[i].second= (1LL * hsh[i-1].second * key[1][1] % mod[1] + s[i]) % mod[1];
    }
  }

  pair<ll,ll> getHash(int l, int r){
    if(l > r || n == 0) return {0, 0};
    pair<ll,ll> R = hsh[r];
    if (l == 0) return R;
    pair<ll,ll> L = hsh[l-1];
    R.first = (1LL * R.first + mod[0] - 1LL * L.first * key[0][r-l+1] % mod[0]) % mod[0];
    R.second = (1LL * R.second + mod[1] - 1LL * L.second * key[1][r-l+1] % mod[1]) % mod[1];
    return R;
  }
};
vector<ll> hashing::key[2];
bool hashing::key_initialized = false;
