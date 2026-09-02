// Algoritma/Fungsi: Kondisi pengecekan gradien pada Convex Hull Trick (CHT) untuk eliminasi garis non-optimal pada optimasi DP.
// Kompleksitas Waktu: Amortized O(1) per penambahan garis, keseluruhan DP O(N).
// NOTE: Menggunakan cross-multiplication (long long) agar tidak ada floating-point precision error.
//       Pastikan slope (m[]) monoton naik/turun agar CHT bekerja dengan benar.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 100005;
int y_coord[N], m[N];

// Returns true if line b is redundant between line a and line c
// Menggunakan cross-multiplication: (yb-ya)*(mb-mc) <= (yc-yb)*(ma-mb)
bool cekx(int a, int b, int c) {
  return (ll)(y_coord[b] - y_coord[a]) * (m[b] - m[c]) <= (ll)(y_coord[c] - y_coord[b]) * (m[a] - m[b]);
}
