// Algoritma/Fungsi: Fast Fourier Transform (FFT) bilangan kompleks untuk perkalian polinomial berpresisi tinggi.
// Kompleksitas Waktu: O(N log N) dengan N ukuran derajat polinomial hasil pembulatan ke pangkat 2.
using ll = long long;
using ld = double;
using cd = complex<ld>;
const ld PI = acos(-(ld)1);

void fft(vector<cd> &a, ll sign = 1) {
    ll n = a.size();

    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }

    for (ll len = 2; len <= n; len <<= 1) {
        ld theta = sign * 2 * PI / len;
        cd wlen(cos(theta), sin(theta));
        for (ll i = 0; i < n; i += len) {
            cd w(1);
            for (ll j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (sign == -1) {
        for (cd &x : a) {
            x /= n;
        }
    }
}

vector<ll> multiply (vector<ll> &a, vector<ll> &b){
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());
    ll n = 1;
    while (n < (a.size() + b.size())){
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);
    fft(fa);
    fft(fb);
    
    for (ll i = 0; i < n; i++){
        fa[i] *= fb[i];
    }

    fft(fa, -1);

    vector<ll> res(n);
    for (ll i = 0; i < n; i++){
        res[i] = round(fa[i].real());
    }
    return res;
}
