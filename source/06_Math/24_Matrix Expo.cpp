template<ll SZ = 2>
struct Mat {
    ll a[SZ][SZ] = {};
    static Mat id() { Mat r; for (ll i = 0; i < SZ; ++i) r.a[i][i] = 1; return r; }
    Mat operator*(const Mat& o) const {
        Mat r;
        for (ll i = 0; i < SZ; ++i)
            for (ll k = 0; k < SZ; ++k) if (a[i][k])
                for (ll j = 0; j < SZ; ++j)
                    r.a[i][j] = (r.a[i][j] + (__int128)a[i][k] * o.a[k][j]) % MOD;
        return r;
    }
    Mat pow(ll p) const {
        Mat r = id(), b = *this;
        for (; p; p >>= 1, b = b * b) if (p & 1) r = r * b;
        return r;
    }
};