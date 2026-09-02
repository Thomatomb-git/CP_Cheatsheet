// Algoritma/Fungsi: Fast I/O membaca dan menulis integer dan string menggunakan low-level I/O tak terkunci (unlocked I/O).
// Kompleksitas Waktu: O(jumlah digit) per operasi baca/tulis.
// NOTE: read() hanya membaca integer. Pastikan input tidak mengandung EOF tak terduga.
//       write(long long) menangani LLONG_MIN secara khusus (lihat kode).
#include <bits/stdc++.h>
using namespace std;

#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif

int read() {
    char c;
    do {
        c = getchar_unlocked();
    } while(c <= 32 && c != -1);
    int res = 0, mul = 1;
    if(c == '-') {
        mul = -1;
        c = getchar_unlocked();
    }
    while('0' <= c && c <= '9') {
        res = res * 10 + (c - '0');
        c = getchar_unlocked();
    }
    return res * mul;
}

void write(long long x) {
    if(x == 0) {
        putchar_unlocked('0');
        return;
    }
    if(x < 0) {
        putchar_unlocked('-');
        if(x == LLONG_MIN) {
            // Tangani khusus: -x dari LLONG_MIN overflow, tulis digit manual
            const char* s = "9223372036854775808";
            while(*s) putchar_unlocked(*s++);
            return;
        }
        x = -x;
    }
    char wbuf[25];
    int idx = 0;
    while(x > 0) {
        wbuf[idx++] = (x % 10) + '0';
        x /= 10;
    }
    for(int i = idx - 1; i >= 0; --i)
        putchar_unlocked(wbuf[i]);
}

void write(const char* s) {
    while(*s) {
        putchar_unlocked(*s);
        ++s;
    }
}
