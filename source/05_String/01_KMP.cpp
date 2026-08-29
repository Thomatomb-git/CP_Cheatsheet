// Algoritma/Fungsi: Knuth-Morris-Pratt (KMP) untuk pencocokan string pola T di dalam teks S dan prekomputasi tabel LPS (pi).
// Kompleksitas Waktu: Prekomputasi O(|T|), Pencarian O(|S| + |T|).
#include <bits/stdc++.h>
using namespace std;

vector<int> compute_lps(const string& t) {
    int n = t.size();
    vector<int> pi(n, 0);
    for(int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while(j > 0 && t[i] != t[j])
            j = pi[j - 1];
        if(t[i] == t[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp_search(const string& s, const string& t) {
    vector<int> matches;
    if(t.empty() || s.empty()) return matches;
    vector<int> pi = compute_lps(t);
    int j = 0;
    for(int i = 0; i < (int)s.size(); i++) {
        while(j > 0 && s[i] != t[j])
            j = pi[j - 1];
        if(s[i] == t[j])
            j++;
        if(j == (int)t.size()) {
            matches.push_back(i - (int)t.size() + 1);
            j = pi[j - 1];
        }
    }
    return matches;
}
