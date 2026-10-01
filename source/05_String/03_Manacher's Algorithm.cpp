// Algoritma Manacher untuk mencari seluruh substring palindrom (panjang ganjil & genap) dan mengecek isPalindrome dalam O(1).
// Prekomputasi O(N), Query isPalindrome O(1).
#define rep(i, a, b) for(int i = (a); i <= (b); ++i)

const int MAX = 1000005;
int lps[MAX * 2];

inline void manacher(const string &str){
  rep(i, 0, 2 * (int)str.size()) lps[i] = 0;
  lps[0] = 0;
  lps[1] = 1;
  int l, r, j, k;
  rep(i, 2, 2 * (int)str.size()){
    l = (i>>1) - (lps[i]>>1);
    r = ((i-1)>>1) + (lps[i]>>1);
    while(1){
      if (l == 0 || r+1 == (int)str.size()) break;
      if (str[l-1] != str[r+1]) break;
      l--, r++;
    }
    lps[i] = r-l+1;
    if (lps[i] > 2){
      j = i-1, k = i+1;
      while (lps[j] - j < lps[i] - i)
        lps[k++] = lps[j--];
      lps[k] = lps[i] - (i-j);
      i = k-1;
    }
  }
}

bool isPalindrome(int l, int r){
  return lps[r + l + 1] >= r - l + 1;
}
