// Algoritma/Fungsi: Menghitung jumlahan floor((a*i + b) / m) untuk i = 0...n-1 dalam O(log(min(m, a))).
// Kompleksitas Waktu: O(log(min(m, a))).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll sum_of_floor(ll n, ll m, ll a, ll b){
  ll ans = 0;
  if (a >= m){
    ans += (n % 2 == 0 ? (n / 2) * (n - 1) : n * ((n - 1) / 2)) * (a / m);
    a %= m;
  }
  if(b >= m){
    ans += n * (b / m);
    b %= m;
  }
  ll y_max = (a * n + b) / m, x_max = (y_max * m - b);
  if (y_max == 0) return ans;
  ans += (n - (x_max + a - 1) / a) * y_max;
  ans += sum_of_floor(y_max, a, m, (a - x_max % a) % a);
  return ans;
}
