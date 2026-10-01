using ll = long long;

struct BigInt {
    vector<int> d; // Digit dibalik: d[0] satuan

    BigInt(ll v = 0) {
        do { d.push_back(v % 10); v /= 10; } while (v > 0);
    }
    BigInt(string s) {
        for (int i = (int)s.size() - 1; i >= 0; i--)
            if (isdigit(s[i])) d.push_back(s[i] - '0');
        trim();
    }
    void trim() {
        while (d.size() > 1 && d.back() == 0) d.pop_back();
    }

    bool operator<(const BigInt &o) const {
        if (d.size() != o.d.size()) return d.size() < o.d.size();
        for (int i = (int)d.size() - 1; i >= 0; i--)
            if (d[i] != o.d[i]) return d[i] < o.d[i];
        return false;
    }
    bool operator==(const BigInt &o) const { return d == o.d; }
    bool operator<=(const BigInt &o) const { return *this < o || *this == o; }
    bool operator>(const BigInt &o) const { return o < *this; }
    bool operator>=(const BigInt &o) const { return !(*this < o); }
    bool operator!=(const BigInt &o) const { return !(*this == o); }

    BigInt operator+(const BigInt &o) const {
        BigInt res; res.d.clear();
        int c = 0;
        for (size_t i = 0; i < max(d.size(), o.d.size()) || c; i++) {
            if (i < d.size()) c += d[i];
            if (i < o.d.size()) c += o.d[i];
            res.d.push_back(c % 10);
            c /= 10;
        }
        return res;
    }

    BigInt operator-(const BigInt &o) const { // Asumsi: *this >= o
        BigInt res = *this;
        int c = 0;
        for (size_t i = 0; i < res.d.size(); i++) {
            int sub = (i < o.d.size() ? o.d[i] : 0) + c;
            if (res.d[i] < sub) { res.d[i] += 10 - sub; c = 1; }
            else { res.d[i] -= sub; c = 0; }
        }
        res.trim();
        return res;
    }

    BigInt operator*(const BigInt &o) const {
        if (*this == 0 || o == 0) return 0;
        BigInt res; res.d.assign(d.size() + o.d.size(), 0);
        for (size_t i = 0; i < d.size(); i++) {
            for (size_t j = 0; j < o.d.size(); j++) {
                res.d[i + j] += d[i] * o.d[j];
                res.d[i + j + 1] += res.d[i + j] / 10;
                res.d[i + j] %= 10;
            }
        }
        res.trim();
        return res;
    }

    BigInt operator/(const BigInt &o) const {
        if (o == 0) throw runtime_error("Division by zero");
        BigInt q, r = 0;
        q.d.resize(d.size());
        for (int i = (int)d.size() - 1; i >= 0; i--) {
            if (r == 0) r.d.clear();
            r.d.insert(r.d.begin(), d[i]);
            r.trim();
            int cnt = 0;
            while (!(r < o)) { r = r - o; cnt++; }
            q.d[i] = cnt;
        }
        q.trim();
        return q;
    }

    BigInt operator%(const BigInt &o) const {
        if (o == 0) throw runtime_error("Division by zero");
        BigInt r = 0;
        for (int i = (int)d.size() - 1; i >= 0; i--) {
            if (r == 0) r.d.clear();
            r.d.insert(r.d.begin(), d[i]);
            r.trim();
            while (!(r < o)) r = r - o;
        }
        return r;
    }

    friend ostream& operator<<(ostream &out, const BigInt &x) {
        for (int i = (int)x.d.size() - 1; i >= 0; i--) out << x.d[i];
        return out;
    }
    friend istream& operator>>(istream &in, BigInt &x) {
        string s; if (in >> s) x = BigInt(s); return in;
    }
};

BigInt power(BigInt a, ll b) {
    BigInt res = 1;
    while (b) { 
        if (b & 1) res = res * a; 
        a = a * a; 
        b >>= 1; 
    }
    return res;
}

BigInt gcd(BigInt a, BigInt b) {
    while (!(b == 0)) {
        BigInt r = a % b;
        a = b;
        b = r;
    }
    return a;
}