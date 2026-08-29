// Algoritma/Fungsi: Mencari semua solusi kongruensi linear ax = b (mod n).
// Kompleksitas Waktu: O(log n + gcd(a, n)).
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int ext_gcd(int a, int b, int &x, int &y) {
    if(b == 0) { x = 1; y = 0; return a; }
    int x1, y1;
    int g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

inline int mod_val(long long a, int m) {
    return (a % m + m) % m;
}

vi modular_linear_equation_solver(int a, int b, int n) {
  int x, y;
  vi ret;
  int g = ext_gcd(a, n, x, y);
  if(b % g == 0) {
    int x0 = mod_val(1LL * x * (b / g), n);
    for(int i = 0; i < g; i++)
      ret.push_back(mod_val(x0 + 1LL * i * (n / g), n));
  }
  return ret;
}
