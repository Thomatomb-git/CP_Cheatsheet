struct WaveletTree {
    int lo, hi;
    WaveletTree *left = nullptr, *right = nullptr;
    vector<int> pref;

    // Build tree dari iterator [from, to) dengan domain nilai [lo, hi]
    WaveletTree(auto from, auto to, int lo, int hi) : lo(lo), hi(hi) {
        if (lo == hi || from >= to) return;
        int mid = lo + (hi - lo) / 2;
        
        pref.reserve(distance(from, to) + 1);
        pref.push_back(0);
        for (auto it = from; it != to; ++it) {
            pref.push_back(pref.back() + (*it <= mid));
        }

        auto pivot = stable_partition(from, to, [mid](int x) { 
            return x <= mid; 
        });

        left = new WaveletTree(from, pivot, lo, mid);
        right = new WaveletTree(pivot, to, mid + 1, hi);
    }

    // 1. K-th Smallest di range [l, r] (1-indexed) -> O(log Sigma)
    int kth(int l, int r, int k) {
        if (lo == hi) return lo;
        int in_left = pref[r] - pref[l - 1];
        if (k <= in_left) {
            return left->kth(pref[l - 1] + 1, pref[r], k);
        } else {
            return right->kth(l - pref[l - 1], r - pref[r], k - in_left);
        }
    }

    // 2. Menghitung banyaknya elemen <= x di range [l, r] -> O(log Sigma)
    int count_lte(int l, int r, int x) {
        if (l > r || x < lo) return 0;
        if (hi <= x) return r - l + 1;
        int mid = lo + (hi - lo) / 2;
        int in_left = pref[r] - pref[l - 1];
        if (x <= mid) {
            return left ? left->count_lte(pref[l - 1] + 1, pref[r], x) : 0;
        } else {
            return in_left + (right ? right->count_lte(l - pref[l - 1], r - pref[r], x) : 0);
        }
    }

    // 3. Menghitung frekuensi kemunculan nilai x di range [l, r] -> O(log Sigma)
    int count_freq(int l, int r, int x) {
        if (l > r || x < lo || x > hi) return 0;
        if (lo == hi) return r - l + 1;
        int mid = lo + (hi - lo) / 2;
        if (x <= mid) {
            return left ? left->count_freq(pref[l - 1] + 1, pref[r], x) : 0;
        } else {
            return right ? right->count_freq(l - pref[l - 1], r - pref[r], x) : 0;
        }
    }

    ~WaveletTree() {
        delete left;
        delete right;
    }
};