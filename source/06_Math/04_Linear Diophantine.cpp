// Menyelesaikan persamaan Diophantine linear ax + by = c dan mencari solusi integer yang meminimalkan |x| + |y|.
// O(log(min(a, b))).
// NOTE: Menangani edge case b=0 (atau a=0) secara terpisah.
//       Jika c % gcd(a,b) != 0, tidak ada solusi (return -1).
typedef long long ll;

ll extgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll x1, y1;
    ll d = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = extgcd(abs(a), abs(b), x0, y0);
    if(c % g != 0) return false;
    x0 *= c / g;
    y0 *= c / g;
    if(a < 0) x0 = -x0;
    if(b < 0) y0 = -y0;
    return true;
}

ll min_abs_sum(ll a, ll b, ll c) {
    ll x0, y0, g;
    if(!find_any_solution(a, b, c, x0, y0, g)) return -1;
    // Edge case: jika b == 0, solusi hanya x0 (tidak bisa geser)
    if(b == 0) return abs(x0) + abs(y0);
    // Edge case: jika a == 0, solusi hanya y0 (tidak bisa geser)
    if(a == 0) return abs(x0) + abs(y0);
    ll step_x = b / g, step_y = a / g;
    ll k = -x0 / step_x;
    ll ans = LLONG_MAX;
    for(ll i = k - 2; i <= k + 2; ++i) {
        ll cur_x = x0 + i * step_x;
        ll cur_y = y0 - i * step_y;
        ans = min(ans, abs(cur_x) + abs(cur_y));
    }
    return ans;
}
