// Algoritma/Fungsi: Uji keprimaan Miller-Rabin deterministik (hingga 2^64) dan faktorisasi prima Pollard's Rho.
// Kompleksitas Waktu: Miller-Rabin O(k log N) (k=12), Pollard's Rho O(N^(1/4) log N).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned __int128 u128;

ll fast(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while(b > 0) {
        if(b & 1) res = (u128)res * a % mod;
        a = (u128)a * a % mod;
        b >>= 1;
    }
    return res;
}

bool miller_rabin(ll n){
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    ll s = 0;
    while (d % 2 == 0){
        s++;
        d /= 2;
    }
    vector<ll> base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (auto a : base){
        if (n <= a) break;
        ll x = fast(a, d, n);
        if (x == 1 || x == n-1) continue;
        bool comp = true;
        for (ll r = 1; r < s; r++){
            x = ((u128)x * x) % n;
            if (x == n-1){
                comp = false;
                break;
            }
        }
        if (comp) return false;
    }
    return true;
}

ll pollard_rho(ll n){
    if (n % 2 == 0) return 2;
    if (n == 1) return 1;
    ll turtle = 2, hare = 2, c = 1, d = 1;
    while (d == 1){
        turtle = (((u128)turtle * turtle) + c) % n;
        hare = (((u128)hare * hare) + c) % n;
        hare = (((u128)hare * hare) + c) % n;
        d = std::gcd(n, llabs(turtle - hare));
        if (d == n){
            c++;
            turtle = 2;
            hare = 2;
            d = 1;
        }
    }
    return d;
}

void factor(ll n, vector<ll> &ans){
    if (n > 1){
        if (miller_rabin(n)){
            ans.push_back(n);
            return;
        }
        ll x = pollard_rho(n);
        factor(x, ans);
        factor(n/x, ans);
    }
}
