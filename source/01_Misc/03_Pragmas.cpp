#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC target("fpmath=387")
#pragma GCC optimize("no-stack-protector") 
// tambahin diatas loop buat ignore vectorization check
#pragma GCC ivdep 

