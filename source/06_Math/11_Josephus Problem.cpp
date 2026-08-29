// Algoritma/Fungsi: Masalah eliminasi Josephus (0-indexed) untuk mencari posisi orang terakhir yang bertahan.
// Kompleksitas Waktu: josephus_fast O(k log n), josephus_linear O(n).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll josephus_fast(ll n, ll k) {
    if(n == 1) return 0;
    if(k == 1) return n - 1;
    if(k > n) return (josephus_fast(n - 1, k) + k) % n;
    ll cnt = n / k;
    ll res = josephus_fast(n - cnt, k);
    res -= n % k;
    if(res < 0) res += n;
    else res += res / (k - 1);
    return res;
}

int josephus_linear(int n, int k) {
    int res = 0;
    for(int i = 1; i <= n; ++i)
        res = (res + k) % i;
    return res;
}
