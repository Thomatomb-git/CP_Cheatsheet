using ll = long long;

// Eksponensiasi modular: (b^e) % m
ll power(ll b, ll e, ll m) {
  ll r = 1 % m; b %= m;
  for (; e > 0; e >>= 1, b = (__int128)b * b % m)
    if (e & 1) r = (__int128)r * b % m;
  return r;
}

// Extended GCD: mencari x, y sehingga a*x + b*y = gcd(a, b)
ll extgcd(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = extgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

// Discrete Log (Extended BSGS): x >= 0 terkecil utk a^x = b (mod m), atau -1. O(sqrt(m))
ll discrete_log(ll a, ll b, ll m) {
  a %= m; b %= m;
  if (m == 1 || b == 1) return 0;
  ll add = 0, k = 1, g;
  while ((g = gcd(a, m)) > 1) {
    if (b == k) return add;
    if (b % g) return -1;
    b /= g; m /= g; ++add;
    k = (__int128)k * (a / g) % m;
  }
  if (b == k) return add;
  ll n = (ll)sqrt(m) + 1, an = power(a, n, m);
  unordered_map<ll, ll> vals;
  // Baby-step: simpan b * a^q mod m -> q
  for (ll q = 0, cur = b; q <= n; ++q, cur = (__int128)cur * a % m) vals[cur] = q;
  // Giant-step: cari (a^n)^p * k = b * a^q (mod m)
  for (ll p = 1, cur = k; p <= n + 1; ++p) {
    cur = (__int128)cur * an % m;
    if (vals.count(cur)) return p * n - vals[cur] + add;
  }
  return -1;
}

// Mencari primitive root (generator) modulo prima p
ll primitive_root(ll p) {
  if (p == 2) return 1;
  vector<ll> fact;
  ll phi = p - 1, tmp = phi;
  for (ll d = 2; d * d <= tmp; ++d) if (tmp % d == 0) {
    fact.push_back(d);
    while (tmp % d == 0) tmp /= d;
  }
  if (tmp > 1) fact.push_back(tmp);
  for (ll g = 2; g < p; ++g) {
    bool ok = true;
    for (ll f : fact) if (power(g, phi / f, p) == 1) { ok = false; break; }
    if (ok) return g;
  }
  return -1;
}

// Discrete Root: semua solusi terurut utk x^a = b (mod p), p prima. O(sqrt(p) log p)
vector<ll> discrete_root(ll a, ll b, ll p) {
  b %= p;
  if (b == 0) return a == 0 ? vector<ll>{} : vector<ll>{0};
  ll g = primitive_root(p), k = discrete_log(g, b, p);
  if (k == -1) return {};
  ll m = p - 1, y0, ty, d = extgcd(a, m, y0, ty);
  if (k % d) return {};
  ll step = m / d;
  y0 = ((__int128)y0 * (k / d) % step + step) % step;
  vector<ll> ans;
  for (ll i = 0; i < d; ++i) ans.push_back(power(g, (y0 + i * step) % m, p));
  sort(ans.begin(), ans.end());
  return ans;
}