// Algoritma/Fungsi: Fenwick Tree (BIT) 1-based index untuk range update dan range sum query.
// Kompleksitas Waktu: Range Update O(log N), Range Query O(log N).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct FenwickRURQ {
    int n;
    vector<ll> bit1, bit2;
    FenwickRURQ(int _n) : n(_n), bit1(_n + 2, 0), bit2(_n + 2, 0) {}

    void updt(vector<ll>& bit, int idx, ll val) {
        for(; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    void update_range(int l, int r, ll val) {
        updt(bit1, l, val);
        updt(bit1, r + 1, -val);
        updt(bit2, l, val * (l - 1));
        updt(bit2, r + 1, -val * r);
    }

    ll query_prefix(int k) {
        ll s1 = 0, s2 = 0;
        for(int i = k; i > 0; i -= i & -i) {
            s1 += bit1[i];
            s2 += bit2[i];
        }
        return s1 * k - s2;
    }

    ll query_range(int l, int r) {
        return query_prefix(r) - query_prefix(l - 1);
    }
};
