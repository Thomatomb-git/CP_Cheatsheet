// Algoritma/Fungsi: Menghitung jumlah derangement !n (permutasi tanpa titik tetap) menggunakan relasi rekurensi D_n = (n-1)(D_{n-1} + D_{n-2}).
// Kompleksitas Waktu: O(N).
// NOTE: Nilai derangement tumbuh sangat cepat, overflow long long di sekitar n=21.
//       Gunakan MOD sesuai kebutuhan soal. Ubah MOD di bawah sesuai problem.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 100005;
const ll MOD = 1e9 + 7;
ll der[N];

void compute_derangements(int n) {
    der[0] = 1;
    der[1] = 0;
    for(int i = 2; i <= n; ++i)
        der[i] = (ll)(i - 1) % MOD * ((der[i - 1] + der[i - 2]) % MOD) % MOD;
}
