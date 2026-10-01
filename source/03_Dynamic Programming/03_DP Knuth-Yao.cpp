// Knuth-Yao DP Optimization untuk optimasi interval DP dengan kondisi quadrangle inequality (opt[i][j-1] <= opt[i][j] <= opt[i+1][j]).
// O(N^2) (tereduksi dari naif O(N^3)).
// NOTE: cost[i][j] harus memenuhi quadrangle inequality agar optimasi valid.
//       Split point k harus memenuhi i < k < j (strict) agar tidak self-reference.
typedef long long ll;

const ll INF = 1e18;
const int N = 1005;
ll dp[N][N];
int opt[N][N];
ll cost[N][N];

void knuth_yao(int n) {
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= n; ++j) {
            dp[i][j] = (j <= i + 1 ? 0 : INF);
            opt[i][j] = i + 1;
        }
    }

    for(int len = 2; len <= n; len++) {
        for(int i = 0; i + len <= n; i++) {
            int j = i + len;
            int sta = opt[i][j - 1];
            int end = opt[i + 1][j];
            dp[i][j] = INF;
            for(int k = max(sta, i + 1); k <= min(end, j - 1); k++) {
                ll val = dp[i][k] + dp[k][j] + cost[i][j];
                if(val < dp[i][j]) {
                    dp[i][j] = val;
                    opt[i][j] = k;
                }
            }
        }
    }
}
