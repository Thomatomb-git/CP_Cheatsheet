mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
T rand_int(T mn, T mx) { //inclusive
    return uniform_int_distribution<T>(mn, mx)(rng);
}
