// Algoritma/Fungsi: Arahan optimasi kompilator GCC (Pragmas) untuk auto-vectorization loop dan peningkatan kecepatan eksekusi.
// Kompleksitas Waktu: Waktu eksekusi bergantung pada kode (pengurangan konstanta runtime).
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC target("fpmath=387")
