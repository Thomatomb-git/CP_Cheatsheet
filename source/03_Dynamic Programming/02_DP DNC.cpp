// Algoritma/Fungsi: Divide and Conquer (D&C) DP Optimization untuk membagi N elemen ke dalam K partisi dengan fungsi biaya monoton.
// Kompleksitas Waktu: O(K * N log N).
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e18;
const int N = 1005, K = 105;
ll dp[K][N];
ll c[N][N];

void compute(int rem, int l, int r, int optl, int optr) {
    if(l > r) return;
    int mid = (l + r) >> 1;
    ll opt_val = INF;
    int opt_id = -1;

    for(int i = optl; i <= min(mid - 1, optr); ++i) {
        ll cur = dp[rem - 1][i] + c[i][mid];
        if(cur < opt_val) {
            opt_val = cur;
            opt_id = i;
        }
    }

    dp[rem][mid] = opt_val;
    if(opt_id == -1) opt_id = optl;
    compute(rem, l, mid - 1, optl, opt_id);
    compute(rem, mid + 1, r, opt_id, optr);
}

void solve(int n, int k) {
    for(int i = 1; i <= n; ++i) dp[1][i] = c[0][i];
    for(int rem = 2; rem <= k; ++rem) {
        compute(rem, rem, n, rem - 1, n);
    }
}
