// Algoritma/Fungsi: Kondisi pengecekan gradien pada Convex Hull Trick (CHT) untuk eliminasi garis non-optimal pada optimasi DP.
// Kompleksitas Waktu: Amortized O(1) per penambahan garis, keseluruhan DP O(N).
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int y_coord[N], m[N];

// Returns true if line b is redundant between line a and line c
bool cekx(int a, int b, int c) {
  return (double)(y_coord[b] - y_coord[a]) / (m[a] - m[b]) <= (double)(y_coord[c] - y_coord[b]) / (m[b] - m[c]);
}
