// Algoritma/Fungsi: 3-Portolan Numbers untuk menghitung jumlah daerah yang terbentuk dari n-seksi sudut pada segitiga sama sisi.
// Kompleksitas Waktu: O(N^2).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solve(ll n){
    ll res = (n % 2 == 1 ? 3 * n * n - 3 * n + 1 : 3 * n * n - 6 * n + 6);
    const int bats = n / 2 - 1;
    for(ll i = 1; i <= bats; i++){
        for(ll j = 1; j <= bats; j++){
            ll num = i * (n - j) * n;
            ll denum = (n - i) * j + i * (n - j);
            res -= 6 * (num % denum == 0 && num / denum <= bats);
        }
    }
    return res;
}
