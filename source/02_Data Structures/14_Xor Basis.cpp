using ll = long long;

template<ll BITS = 60>
struct XorBasis {
    ll basis[BITS];
    ll sz = 0;

    XorBasis() {
        memset(basis, 0, sizeof(basis));
    }

    // Memasukkan elemen ke dalam basis.
    // Mengembalikan 1 (true) jika elemen independen, 0 (false) jika tidak.
    bool insert(ll mask) {
        for (ll i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = mask;
                    sz++;
                    return true;
                }
                mask ^= basis[i];
            }
        }
        return false;
    }

    // Memeriksa apakah suatu nilai bisa dibentuk dari subset elemen
    bool can_form(ll mask) const {
        for (ll i = BITS - 1; i >= 0; --i) {
            if ((mask >> i) & 1) {
                if (!basis[i]) return false;
                mask ^= basis[i];
            }
        }
        return true;
    }

    // Mendapatkan nilai XOR maksimum yang bisa dibentuk
    ll get_max() const {
        ll ans = 0;
        for (ll i = BITS - 1; i >= 0; --i) {
            if ((ans ^ basis[i]) > ans) {
                ans ^= basis[i];
            }
        }
        return ans;
    }

    // Mendapatkan nilai XOR minimum (non-zero) yang bisa dibentuk
    ll get_min() const {
        for (ll i = 0; i < BITS; ++i) {
            if (basis[i]) return basis[i];
        }
        return 0;
    }

    // Menggabungkan dua basis
    void merge(const XorBasis& other) {
        for (ll i = BITS - 1; i >= 0; --i) {
            if (other.basis[i]) {
                insert(other.basis[i]);
            }
        }
    }

    // Mendapatkan nilai XOR terkecil ke-k (1-indexed) dari semua kombinasi subset distinct
    ll kth_smallest(ll k) const {
        // Reduksi basis ke bentuk kanonik (Reduced Row Echelon Form)
        ll reduced[BITS];
        memcpy(reduced, basis, sizeof(basis));
        for (ll i = 0; i < BITS; ++i) {
            if (!reduced[i]) continue;
            for (ll j = i + 1; j < BITS; ++j) {
                if ((reduced[j] >> i) & 1) {
                    reduced[j] ^= reduced[i];
                }
            }
        }

        vector<ll> v;
        for (ll i = 0; i < BITS; ++i) {
            if (reduced[i]) v.push_back(reduced[i]);
        }

        ll num_distinct = (1LL << (ll)v.size());
        if (k > num_distinct) return -1; // k melebihi jumlah kombinasi unik

        ll ans = 0;
        for (ll i = 0; i < (ll)v.size(); ++i) {
            if ((k >> i) & 1) {
                ans ^= v[i];
            }
        }
        return ans;
    }
};