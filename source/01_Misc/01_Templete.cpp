// Algoritma/Fungsi: Template dasar competitive programming dengan Fast I/O, 64-bit RNG, pb_ds ordered_set, dan gp_hash_table anti-hack.
// Kompleksitas Waktu: Fast I/O O(1), gp_hash_table average O(1) lookup, ordered_set O(log N) insert/query/order.
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// 64-bit RNG
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Custom hash to prevent anti-hash test cases
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// pb_ds ordered_set & gp_hash_table
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V> using gpmap = gp_hash_table<K, V, custom_hash>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}
