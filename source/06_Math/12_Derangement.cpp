typedef long long ll;
const int N = 100005;
const ll MOD = 1e9 + 7;
ll der[N];

void compute_derangements(int n) {
    der[0] = 1;
    der[1] = 0;
    for(int i = 2; i <= n; ++i)
        der[i] = (ll)(i - 1) % MOD * ((der[i - 1] + der[i - 2]) % MOD) % MOD;
}
