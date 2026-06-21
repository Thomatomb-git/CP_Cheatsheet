// Pre : fast expo
// prime = true, composite = false
bool miller_rabin(ll n){ // O(k * log n)
    if (n == 1) return false;
    ll d = n-1;
    ll s = 0;
    while (d % 2 == 0){
        s++;
        d /= 2;
    }
    vector<ll> base = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; //deterministic up to 2^64 - 1
    for (auto a : base){
        if (n <= a) break;

        ll x = fast(a, d, n);
        if (x == 1 || x == n-1) continue;

        bool comp = true;
        for (ll r = 1; r < s; r++){
            x = ((u128)x * x) % n;
            if (x == n-1){
                comp = false;
                break;
            }
        }

        if (comp) return false;
    }
    return true;
}

// output random factor of n
ll pollard_rho (ll n){ // O(n^(1/4) log n)
    if (n % 2 == 0) return 2;
    if (n == 1) return 1;

    ll turtle = 2; // turtle, hare, c can be randomize
    ll hare = 2;
    ll c = 1; // f(x) = (x^2 + c) mod n
    ll d = 1;

    while (d == 1){
        turtle = (((u128)turtle * turtle) + c) % n;
        hare = (((u128)hare * hare) + c) % n;
        hare = (((u128)hare * hare) + c) % n;

        d = gcd(n, llabs(turtle - hare));

        if (d == n){
            c++;
            turtle = 2;
            hare = 2;
            d = 1;
        }
    }
    return d;
}

void factor(ll n, vector<ll> &ans){ // O(n^(1/4) log n)
    if (n > 1){
        if (miller_rabin(n)){
            ans.push_back(n);
            return;
        }

        ll x = pollard_rho(n);
        factor(x, ans);
        factor(n/x, ans);
    }
}
