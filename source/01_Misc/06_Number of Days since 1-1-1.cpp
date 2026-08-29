// Algoritma/Fungsi: Algoritma Rata Die untuk menghitung total jumlah hari yang telah berlalu sejak 1 Januari 0001.
// Kompleksitas Waktu: O(1).
#include <bits/stdc++.h>
using namespace std;

int rdn(int d, int m, int y) {
    if(m < 3) --y, m += 12;
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}
