// Algoritma/Fungsi: Mengubah bilangan bulat positif menjadi representasi angka Romawi standar.
// Kompleksitas Waktu: O(1) (terbatas oleh rentang representasi angka Romawi).
#include <bits/stdc++.h>
using namespace std;

const string R[] = {
    "M", "CM", "D", "CD", "C", "XC", "L",
    "XL", "X", "IX", "V", "IV", "I"
};

const int N[] = {
    1000, 900, 500, 400, 100, 90, 50, 40, 10,
    9, 5, 4, 1
};

string to_roman(int x) {
    if(x == 0)
        return "N";
    string res = "";
    for(int i = 0; i < 13; ++i) {
        while(x >= N[i]) {
            x -= N[i];
            res += R[i];
        }
    }
    return res;
}
