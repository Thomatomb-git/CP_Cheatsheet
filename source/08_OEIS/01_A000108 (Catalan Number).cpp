// Algoritma/Fungsi: Menghitung Bilangan Catalan C(n) = C(2n, n) / (n+1) dan Bilangan Super Catalan (Schroder).
// Kompleksitas Waktu: Catalan DP O(N^2), Super Catalan O(N).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll findCatalan(int n) {
    if(n <= 1) return 1;
    vector<ll> catalan(n + 1, 0);
    catalan[0] = catalan[1] = 1;
    for(int i = 2; i <= n; i++) {
        for(int j = 0; j < i; j++)
            catalan[i] += catalan[j] * catalan[i - j - 1];
    }
    return catalan[n];
}

ll superCat(int n) {
    if(n <= 1) return 1;
    vector<ll> s(n + 1, 0);
    s[0] = s[1] = 1;
    for(int i = 2; i <= n; ++i) {
        s[i] = (3 * (2 * i - 1) * s[i - 1] - (i - 2) * s[i - 2]) / (i + 1);
    }
    return s[n];
}
