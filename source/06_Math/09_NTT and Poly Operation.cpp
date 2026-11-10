namespace FFT {
#define ll long long

// ============== Adjust the constants here ============== //
const int LN = 23; // 24 (Tip: lower to 19 or 20 if max N <= 5e5 to speed up init_fft)
const int N = 1 << LN;

// 'MOD' must be of the form 2^LN * k + 1, where k odd.
const int MOD = 998244353; // 2**23 * 119 + 1.
//const ll MOD = 9223372036737335297; // 2**24 * 54975513881 + 1.
const int PRIMITIVE_ROOT = 3; // Primitive root modulo 'MOD'.
// ==================== End of constants ==================== //

int root[N];

inline void init_fft() {
  const int UNITY = fast(PRIMITIVE_ROOT, (MOD - 1) >> LN, MOD);
  root[0] = 1;
  for (int i = 1; i < N; i++)
    root[i] = (ll)UNITY * root[i - 1] % MOD;
  return;
}

inline void fft(int n, vector<int> &a, bool invert) {
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j >= bit; bit >>= 1) j -= bit;
    j += bit;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    int wlen = (invert ? root[N - N / len] : root[N / len]);
    for (int i = 0; i < n; i += len) {
      int w = 1;
      for (int j = 0; j < (len >> 1); j++) {
        unsigned int u = a[i + j];
        unsigned int v = (ll)a[i + j + len / 2] * w % MOD;
        a[i + j] = (u + v) % MOD;
        a[i + j + len / 2] = (u - v + MOD) % MOD;
        w = (ll)w * wlen % MOD;
      }
    }
  }
  if (invert) {
    int inv = fast(n, MOD - 2, MOD);
    for (int i = 0; i < n; i++) a[i] = (ll)a[i] * inv % MOD;
  }
  return;
}

#undef ll
}

namespace Polynomial {
using namespace FFT;
#define ll long long
const int Imaginary = 86583718; // sqrt(-1) mod 998244353

inline vector<int> multiply(vector<int> a, vector<int> b) {
  if (a.empty() || b.empty()) return {};
  int n = 1, as = a.size(), bs = b.size();
  while (n <= as + bs - 2) n <<= 1;

  vector<int> c;
  a.resize(n, 0); b.resize(n, 0); c.resize(n);

  fft(n, a, false); fft(n, b, false);
  for (int i = 0; i < n; ++i)
    c[i] = (ll)a[i] * b[i] % MOD;
  fft(n, c, true);
  return c;
}

inline vector<int> inverse(vector<int> a) {
  int n = 1; while (n < (int)a.size()) n <<= 1;
  a.resize(n, 0); // FIX: prevent out-of-bounds access when a.size() < n

  vector<int> b = {fast(a[0], MOD - 2, MOD)};
  for (int l = 2; l <= n; l <<= 1) {
    vector<int> t(l << 1, 0);
    for (int i = 0; i < l; i++) t[i] = a[i];

    b.resize(l << 1, 0);
    fft(l << 1, t, false); fft(l << 1, b, false);
    for (int i = 0; i < (l << 1); i++)
      b[i] = ((2 - 1ll * t[i] * b[i]) % MOD * b[i] % MOD + MOD) % MOD;
    fft(l << 1, b, true);
    b.resize(l);
  }
  return b;
}

inline vector<int> integral(vector<int> a) {
  int n = a.size();
  for (int i = n - 1; i >= 1; i--) {
    a[i] = 1ll * a[i - 1] * fast(i, MOD - 2, MOD) % MOD;
  }
  if (n > 0) a[0] = 0;
  return a;
}

inline vector<int> derivative(vector<int> a) {
  int n = a.size();
  for (int i = 0; i < n - 1; i++) {
    a[i] = 1ll * a[i + 1] * (i + 1) % MOD;
  }
  if (n > 0) a[n - 1] = 0;
  return a;
}

inline vector<int> ln(vector<int> a) {
  int n = 1; while (n < (int)a.size()) n <<= 1;
  a.resize(n, 0);

  vector<int> b = inverse(a);
  a = derivative(a);

  a = multiply(a, b);
  a.resize(n);
  return integral(a);
}

inline vector<int> exp(vector<int> a) {
  int n = 1; while (n < (int)a.size()) n <<= 1;
  a.resize(n, 0); // FIX: prevent out-of-bounds access

  vector<int> b = {1};
  for (int l = 2; l <= n; l <<= 1) {
    b.resize(l);
    vector<int> t = ln(b);
    for (int i = 0; i < l; i++) {
      t[i] = (a[i] - t[i] + MOD) % MOD;
    }
    t[0] = (t[0] + 1) % MOD;

    b = multiply(t, b);
    b.resize(l);
  }
  return b;
}

inline vector<int> sqrt(vector<int> a) {
  int n = 1; while (n < (int)a.size()) n <<= 1;
  a.resize(n, 0); // FIX: prevent out-of-bounds access

  vector<int> b{1};
  int inv2 = fast(2, MOD - 2, MOD);
  for (int l = 2; l <= n; l <<= 1) {
    b.resize(l);
    vector<int> t = inverse(b), r(l);
    for (int i = 0; i < l; i++) r[i] = a[i];

    t = multiply(t, r);
    for (int i = 0; i < l; i++)
      b[i] = 1ll * (b[i] + t[i]) * inv2 % MOD;
  }
  return b;
}

inline vector<int> sin(vector<int> a) {
  int n = 1; while (n < (int)a.size()) n <<= 1;
  a.resize(n, 0); // FIX: prevent out-of-bounds access

  for (int i = 0; i < n; i++)
    a[i] = 1ll * a[i] * Imaginary % MOD;
  vector<int> t = exp(a), ans = t;
  t = inverse(t);
  int inv = fast(2 * Imaginary, MOD - 2, MOD);
  for (int i = 0; i < n; i++)
    ans[i] = (1ll * (ans[i] - t[i]) * inv % MOD + MOD) % MOD;
  return ans;
}

inline vector<int> cos(vector<int> a) {
  int n = 1; while (n < (int)a.size()) n <<= 1;
  a.resize(n, 0); // FIX: prevent out-of-bounds access

  for (int i = 0; i < n; i++)
    a[i] = 1ll * a[i] * Imaginary % MOD;
  vector<int> t = exp(a), ans = t;
  t = inverse(t);
  int inv2 = fast(2, MOD - 2, MOD);
  for (int i = 0; i < n; i++)
    ans[i] = 1ll * (ans[i] + t[i]) * inv2 % MOD;
  return ans;
}

#undef ll
}