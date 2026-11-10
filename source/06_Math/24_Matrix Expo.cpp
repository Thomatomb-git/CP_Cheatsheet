using vvll = vector<vector<ll>>;
vvll matmul (vvll &a, vvll &b){
  vvll res (a.size(), vector<ll>(b[0].size(), 0));
  for (ll i = 0; i < a.size(); i++){
    for (ll j = 0; j < b[0].size(); j++){
      for (ll k = 0; k < a[0].size(); k++){
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return res;
}

// only can for N x N
vvll matexpo (vvll a, ll b){
  vvll res (a.size(), vector<ll> (a[0].size(), 0));
  for (ll i = 0; i < a.size(); i++) res[i][i] = 1;

  while (b > 0){
    if (b & 1) res = matmul(res, a);
    a = matmul(a, a);
    b /= 2;
  }
  return res;
}