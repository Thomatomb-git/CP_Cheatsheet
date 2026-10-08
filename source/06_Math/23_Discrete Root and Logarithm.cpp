using ll = long long;

// Eksponensiasi Modular: (base^exp) % mod
ll power(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Extended GCD: a*x + b*y = gcd(a, b)
ll extgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll x1, y1;
    ll d = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// Invers Modular: a^(-1) mod m
ll mod_inv(ll a, ll m) {
    ll x, y;
    ll g = extgcd(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

// ============================================================================
// KASUS 2: Discrete Logarithm (a^x = b mod m)
// Mendukung m sembarang (Extended BSGS)
// Mengembalikan nilai x non-negatif terkecil, atau -1 jika tidak ada solusi.
// Kompleksitas: O(sqrt(m))
// ============================================================================
ll solve_discrete_log(ll a, ll b, ll m) {
    a %= m; b %= m;
    if (m == 1) return 0;
    if (b == 1) return 0;

    ll add = 0, k = 1;
    ll g = std::gcd(a, m);

    while (g > 1) {
        if (b == k) return add;
        if (b % g != 0) return -1;

        b /= g;
        m /= g;
        k = (__int128)k * (a / g) % m;
        add++;
        g = std::gcd(a, m);
    }

    // Standard BSGS pada sub-masalah: (a^x) * k = b (mod m) dengan gcd(a, m) = 1
    ll n = sqrt(m) + 1;
    unordered_map<ll, ll> vals;

    // Baby-step: vals[k * a^q mod m] = q
    ll cur = k;
    for (ll q = 0; q <= n; ++q) {
        vals[cur] = q;
        cur = (__int128)cur * a % m;
    }

    // Giant-step: periksa (a^n)^p mod m
    ll an = power(a, n, m);
    cur = 1;
    for (ll p = 1; p <= n; ++p) {
        cur = (__int128)cur * an % m;
        // Ingin mencari cur * a^(-q) = b/k mod m <=> cur = (k * a^q) mod m
        // Kita bandingkan jika cur cocok dengan tabel baby-step yang dinormalisasi dengan b
        // Lebih sederhana: cari cur * inv(b) di tabel baby-step
    }

    // Pendekatan alternatif tanpa invers per giant step:
    // a^(p*n - q) * k = b <=> (a^n)^p * k = b * a^q
    vals.clear();
    ll cur_b = b;
    for (ll q = 0; q <= n; ++q) {
        vals[cur_b] = q;
        cur_b = (__int128)cur_b * a % m;
    }

    cur = k;
    for (ll p = 1; p <= n + 1; ++p) {
        cur = (__int128)cur * an % m;
        if (vals.count(cur)) {
            ll ans = p * n - vals[cur] + add;
            return ans;
        }
    }

    return -1;
}

// ============================================================================
// KASUS 1: Discrete Root (x^a = b mod p) dengan p bilangan prima
// Mengembalikan semua solusi x mod p dalam vector terurut
// Kompleksitas: O(sqrt(p) log p)
// ============================================================================

// Mencari generator / Primitive Root modulo p prima
ll find_primitive_root(ll p) {
    if (p == 2) return 1;
    vector<ll> fact;
    ll phi = p - 1, temp = phi;

    for (ll d = 2; d * d <= temp; ++d) {
        if (temp % d == 0) {
            fact.push_back(d);
            while (temp % d == 0) temp /= d;
        }
    }
    if (temp > 1) fact.push_back(temp);

    for (ll g = 2; g < p; ++g) {
        bool ok = true;
        for (ll factor : fact) {
            if (power(g, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return -1;
}

vector<ll> solve_discrete_root(ll a, ll b, ll p) {
    b %= p;
    if (b == 0) {
        if (a == 0) return {}; // 0^0 tidak terdefinisi
        return {0};
    }

    ll g = find_primitive_root(p);

    // Langkah 1: Selesaikan g^k = b (mod p) menggunakan BSGS
    ll k = solve_discrete_log(g, b, p);
    if (k == -1) return {};

    // Langkah 2: Selesaikan a * y = k (mod p - 1)
    ll m = p - 1;
    ll y0, temp_y;
    ll d = extgcd(a, m, y0, temp_y);

    if (k % d != 0) return {}; // Tidak ada solusi jika d tidak membagi k

    // Basis solusi pertama:
    y0 = ((__int128)y0 * (k / d)) % (m / d);
    if (y0 < 0) y0 += (m / d);

    // Langkah 3: Bangkitkan semua d solusi unik
    vector<ll> ans;
    ll step = m / d;
    for (ll i = 0; i < d; ++i) {
        ll y = (y0 + i * step) % m;
        ans.push_back(power(g, y, p));
    }

    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Contoh Soal 2: 2^x = 13 (mod 59)
    ll a2 = 2, b2 = 13, m2 = 59;
    ll x2 = solve_discrete_log(a2, b2, m2);
    cout << "[Soal 2] " << a2 << "^x = " << b2 << " mod " << m2 << "\n";
    cout << "x = " << x2 << "\n\n";

    // Contoh Soal 1: x^3 = 8 (mod 11)
    ll a1 = 3, b1 = 8, p1 = 11;
    vector<ll> ans1 = solve_discrete_root(a1, b1, p1);
    cout << "[Soal 1] x^" << a1 << " = " << b1 << " mod " << p1 << "\n";
    cout << "Solusi x: ";
    for (ll sol : ans1) cout << sol << " ";
    cout << "\n";

    return 0;
}