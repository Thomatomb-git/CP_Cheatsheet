// Algoritma/Fungsi: Generator bilangan acak 64-bit terdistribusi seragam dalam rentang [mn, mx] inklusif.
// Kompleksitas Waktu: O(1) per pemanggilan.
#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
T rand_int(T mn, T mx) {
    return uniform_int_distribution<T>(mn, mx)(rng);
}
