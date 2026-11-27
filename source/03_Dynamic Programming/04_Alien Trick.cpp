// Aliens Trick (WQS Binary Search): menghilangkan dimensi K pada DP O(N*K) -> O(N log C).
// Syarat:
//   - Minimasi  : f(k) harus convex  (f(k+1) - f(k) non-decreasing).
//   - Maksimasi : f(k) harus concave (f(k+1) - f(k) non-increasing).
// Kompleksitas: O(T_dp * log(MAX_PENALTY))
using ll = long long;

// Contoh untuk MINIMASI: mengembalikan {min(cost + lambda * cnt), cnt}
// PENTING (Tie-break): jika cost sama, pilih cnt TERKECIL!
pair<ll, ll> solve_dp(ll lambda) {
  // ... jalankan DP tanpa batasan K, tambah (+ lambda) setiap ambil 1 segmen/item ...
  // Untuk MAKSIMASI: kurangi (- lambda) setiap ambil 1 item, tie-break tetap cnt terkecil.
  return {best_val, best_cnt};
}

ll aliens_min(ll K, ll lo, ll hi) { // lo = -MAX_C (atau 0 jika f(k) monoton turun), hi = MAX_C
  ll ans = 0;
  while (lo <= hi) {
    ll mid = lo + (hi - lo) / 2;
    auto [val, cnt] = solve_dp(mid);
    if (cnt <= K) {
      ans = val - mid * K; // WAJIB pakai K (bukan cnt) agar aman saat titik kolinear!
      hi = mid - 1;        // kecilkan penalti agar cnt mendekati K
    } else {
      lo = mid + 1;        // besarkan penalti agar cnt turun
    }
  }
  return ans;
}