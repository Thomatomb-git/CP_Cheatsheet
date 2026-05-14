int lps[MAX * 2];
inline void manacher(string &str){
  rep(i, 0, 2*str.size()) lps[i] = 0;
  lps[0] = 0;
  lps[1]=1;
  int l, r, j, k;
  rep(i, 2, 2*str.size()){
    l = (i>>1) - (lps[i]>>1);
    r = ((i-1)>>1) + (lps[i]>>1);
    while(1){//widen
      if (l == 0 || r+1 == str.size()) break;
      if (str[l-1] != str[r+1]) break;
      l--, r++;
    }
    lps[i] = r-l+1;
    //jump
    if (lps[i] > 2){
      j = i-1, k = i+1; //while lps[j] inside lps[i]
      while (lps[j] - j < lps[i] - i)
        lps[k++] = lps[j--];
      lps[k] = lps[i] - (i-j); //lps[k] <- edge of lps[i]
      i = k-1; //jump to mirror, which is k
    }
  }
  return;
}
//Cara dapetin suatu lps(ganjil atau genap)
//bakal cover dari index-0 berapa sampe berapa
//maka L = (i-lps[i]>>1), R=(i+lps[i]>>1)-1;
bool isPalindrome(int l, int r){return lps[r+l+1] >= r-l+1;}