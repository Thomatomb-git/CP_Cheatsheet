// Algoritma/Fungsi: Extended Euclidean Algorithm untuk menghitung gcd(a, b) serta koefisien Bezout x, y (ax + by = gcd(a, b)).
// Kompleksitas Waktu: O(log(min(a, b))).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

tuple<ll, ll, ll> gcd(ll a, ll b) {
  if(b == 0) return {a, 1, 0};
  auto [d, x1, y1] = gcd(b, a % b);
  return {d, y1, x1 - y1 * (a / b)};
}
