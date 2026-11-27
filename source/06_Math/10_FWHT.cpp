// Kompleksitas: O(N log N), dengan N = pangkat 2 terkecil >= max(|a|, |b|).
// op: 0 = XOR, 1 = OR, 2 = AND
using ll = long long;

void fwht(vector<ll> &a, bool inv, ll op) {
  ll n = a.size();
  for (ll len = 1; len < n; len <<= 1) {
    for (ll i = 0; i < n; i += len << 1) {
      for (ll j = 0; j < len; ++j) {
        ll u = a[i + j], v = a[i + j + len];
        if (op == 0) { // XOR
          a[i + j] = u + v;
          a[i + j + len] = u - v;
        } else if (op == 1) { // OR
          a[i + j + len] = inv ? v - u : v + u;
        } else { // AND
          a[i + j] = inv ? u - v : u + v;
        }
      }
    }
  }
  if (inv && op == 0) {
    for (ll &x : a) x /= n;
  }
}
// Menghitung c[k] = sum(a[i] * b[j]) untuk semua (i op j == k)
vector<ll> convolve(vector<ll> a, vector<ll> b, ll op) {
  ll n = 1, sz = max(a.size(), b.size());
  while (n < sz) n <<= 1;
  a.resize(n, 0); b.resize(n, 0);
  fwht(a, false, op);
  fwht(b, false, op);
  for (ll i = 0; i < n; ++i) a[i] *= b[i];
  fwht(a, true, op);
  return a;
}