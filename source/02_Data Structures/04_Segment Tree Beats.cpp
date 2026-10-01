// Segment Tree Beats untuk operasi range chmin (A_i = min(A_i, v)), range max query, dan range sum query.
// Amortized O((N + Q) log N) untuk seluruh operasi.
using ll = long long;

const int N = 200005;
const ll INF = 1e18;

ll ST1[4 * N + 5], ST2[4 * N + 5];
ll smax[4 * N + 5], occ[4 * N + 5];
ll arr[N + 5];

void pushup(int idx) {
    ST1[idx] = max(ST1[2 * idx], ST1[2 * idx + 1]);
    ST2[idx] = ST2[2 * idx] + ST2[2 * idx + 1];
    if(ST1[2 * idx] == ST1[2 * idx + 1]) {
        smax[idx] = max(smax[2 * idx], smax[2 * idx + 1]);
        occ[idx] = occ[2 * idx] + occ[2 * idx + 1];
    } else {
        smax[idx] = min(ST1[2 * idx], ST1[2 * idx + 1]);
        smax[idx] = max(smax[idx], max(smax[2 * idx], smax[2 * idx + 1]));
        if(ST1[2 * idx] > ST1[2 * idx + 1])
            occ[idx] = occ[2 * idx];
        else
            occ[idx] = occ[2 * idx + 1];
    }
}

void build(int idx, int l, int r) {
    if(l == r) {
        ST1[idx] = ST2[idx] = arr[l];
        occ[idx] = 1;
        smax[idx] = -INF;
        return;
    }
    int mid = (l + r) >> 1;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
    pushup(idx);
}

void pushdown(int idx, ll v) {
    if(ST1[idx] <= v) return;
    assert(v > smax[idx]);
    ST2[idx] -= (ST1[idx] - v) * occ[idx];
    ST1[idx] = v;
}

void down(int idx) {
    pushdown(2 * idx, ST1[idx]);
    pushdown(2 * idx + 1, ST1[idx]);
}

void update_chmin(int idx, int l, int r, int le, int ri, ll v) {
    if(r < le || ri < l || ST1[idx] <= v)
        return;
    if(le <= l && r <= ri && smax[idx] < v) {
        pushdown(idx, v);
        return;
    }
    down(idx);
    int mid = (l + r) >> 1;
    update_chmin(2 * idx, l, mid, le, ri, v);
    update_chmin(2 * idx + 1, mid + 1, r, le, ri, v);
    pushup(idx);
}

ll query_max(int idx, int l, int r, int le, int ri) {
    if(r < le || ri < l)
        return -INF;
    if(le <= l && r <= ri)
        return ST1[idx];
    down(idx);
    int mid = (l + r) >> 1;
    return max(query_max(2 * idx, l, mid, le, ri),
               query_max(2 * idx + 1, mid + 1, r, le, ri));
}

ll query_sum(int idx, int l, int r, int le, int ri) {
    if(r < le || ri < l)
        return 0;
    if(le <= l && r <= ri)
        return ST2[idx];
    down(idx);
    int mid = (l + r) >> 1;
    return query_sum(2 * idx, l, mid, le, ri) +
           query_sum(2 * idx + 1, mid + 1, r, le, ri);
}
