// Algoritma/Fungsi: Menghitung jumlah derangement !n (permutasi tanpa titik tetap) menggunakan relasi rekurensi D_n = (n-1)(D_{n-1} + D_{n-2}).
// Kompleksitas Waktu: O(N).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 100005;
ll der[N];

void compute_derangements(int n) {
    der[0] = 1;
    der[1] = 0;
    for(int i = 2; i <= n; ++i)
        der[i] = (ll)(i - 1) * (der[i - 1] + der[i - 2]);
}
