#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

// random 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
// pb_ds stuff
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { int operator()(int x) const { return x ^ RANDOM; }};
 
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V> using gpmap = gp_hash_table<K, V, chash>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
}
