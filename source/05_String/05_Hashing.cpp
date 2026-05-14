class hashing{
public:
  int n;
  string s;
  int mod[2] = {1000000007,1000000009};
  vector<ll> key[2];
  vector<pair<ll,ll>> hsh;
  hashing(string _s) : s(_s){
    n = (int) s.size();
    for(int i = 0; i < 2;i++){
      key[i].resize(n+1);
      key[i][0] = 1;
      do{
        key[i][1] = rng() % mod[i];
        if (key[i][1] < 0) key[i][1] += mod[i];
      } while(key[i][1] == 0);
      for (int j = 2; j <= n; j++){
        key[i][j]=1LL * key[i][j-1] * key[i][1] % mod[i];
      }
    }
    hsh.resize(n);
    hsh[0] = {s[0], s[0]};
    for (int i = 1; i < n; i++){
      hsh[i].first = (1LL * hsh[i-1].first * key[0][1] % mod[0] + s[i]) % mod[0];
      hsh[i].second= (1LL * hsh[i-1].second * key[1][1] % mod[1] + s[i]) % mod[1];
    }
  }
  pair<ll,ll>getHash(int l, int r){
    pair<ll,ll> R = hsh[r];
    if (l == 0){
      return R;
    }
    pair<ll,ll> L = hsh[l-1];
    R.first = (1LL * R.first + mod[0] - 1LL * L.first * key[0][r-l+1] % mod[0]) % mod[0];
    R.second =(1LL * R.second + mod[1] - 1LL * L.second * key[1][r-l+1] % mod[1]) % mod[1];
    return R;
  }
};