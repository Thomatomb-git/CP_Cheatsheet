// Algoritma/Fungsi: Generalized Lucas Theorem untuk menghitung kombinasi C(n, r) modulo prime power (p^k).
// Kompleksitas Waktu: O(p^k + log_p n).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fast(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while(b > 0) {
        if(b & 1) res = (__int128)res * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return res;
}

ll totient(ll n) {
    ll result = n;
    for(ll p = 2; p * p <= n; ++p) {
        if(n % p == 0) {
            while(n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if(n > 1) result -= result / n;
    return result;
}

ll E(ll n, ll p) {
    ll tot = 0;
    while(n != 0) {
        tot += n / p;
        n /= p;
    }
    return tot;
}

ll F(ll n, ll p, ll pk, const vector<ll>& fctp) {
    ll ans = 1;
    while(n > 0) {
        ans = (__int128)ans * fast(fctp[pk], n / pk, pk) % pk * fctp[n % pk] % pk;
        n /= p;
    }
    return ans;
}

ll prime_power_lucas(ll n, ll r, ll p, ll pk) {
    if(r < 0 || r > n) return 0;
    vector<ll> fctp(pk + 1, 1);
    for(ll i = 1; i <= pk; ++i) {
        fctp[i] = fctp[i - 1];
        if(i % p != 0) fctp[i] = (fctp[i] * (i % pk)) % pk;
    }

    ll power = E(n, p) - E(n - r, p) - E(r, p);
    if(power >= 60 || fast(p, power, pk) == 0) return 0;

    ll top = fast(p, power, pk) * F(n, p, pk, fctp) % pk;
    ll bot = F(r, p, pk, fctp) * F(n - r, p, pk, fctp) % pk;
    ll bot_inv = fast(bot, totient(pk) - 1, pk);
    return (top * bot_inv) % pk;
}
