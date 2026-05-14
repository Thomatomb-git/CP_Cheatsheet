//s = string, t = pattern
//result is in 0-index (points to the index that matches)
int lps[t.size() + 1];
inline void precalc(string t){
  lps[0] = -1;
  for (int i = 1; i < (int)t.size(); i++){
    int j = lps[i-1];
    while (j >= 0 && t[i] != t[j+1]) j = lps[j];
    lps[i] = (t[i] == t[j+1]) ? (j+1) : -1;
  }
}
bool kmp(string s){
  for (int i = 0, j = -1; i < (int)s.size(); i++){
    while (j >= 0 && s[i] != t[j+1]) j = lps[j];
    if (s[i] == t[j+1]) j++;
    if (j == (int)t.size()-1) return 1;
  }
  return 0;
}