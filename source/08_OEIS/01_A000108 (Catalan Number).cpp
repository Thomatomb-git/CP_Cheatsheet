//C(2n,n)/(n+1) == C(2n,n)-C(2n,n-1)
//1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012
int findCatalan(int n){
  int catalan[n + 1];
  catalan[0] = catalan[1] = 1;
  for (int i = 2; i <= n; i++){
    catalan[i] = 0;
    for (int j = 0; j < i; j++)
      catalan[i] += catalan[j] * catalan[i - j - 1];
  }
  return catalan[n];
}

//C(2m,m)*C(2n,n)/C(m+n,m)
//1,1,3,11,45,197,903,4279,20793,103049,518859,2646723  
ll superCat(int n){
  if (n <= 1) return 1;
  return (3 * (2*n - 1) * superCat(n-1) - 
    (n-2) * superCat(n-2)) / (n+1);
}