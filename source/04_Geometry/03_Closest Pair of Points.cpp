// Algoritma/Fungsi: Divide and Conquer untuk mencari pasangan dua titik 2D dengan jarak Euclidean terdekat.
// Kompleksitas Waktu: O(N log N) atau O(N log^2 N).
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
typedef pair<int, int> pii;

struct Point {
    int x, y, id;
};

double dist(Point p1, Point p2) {
    return hypot((double)(p1.x - p2.x), (double)(p1.y - p2.y));
}

pair<pii, double> bruteForce(Point P[], int n) {
    double mn = 1e18;
    pii ret = {-1, -1};
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            double d = dist(P[i], P[j]);
            if(d < mn) {
                ret = {P[i].id, P[j].id};
                mn = d;
            }
        }
    }
    return {ret, mn};
}

pair<pii, double> getmin(pair<pii, double> a, pair<pii, double> b) {
    if(a.fi.fi == -1) return b;
    if(b.fi.fi == -1) return a;
    return (a.se < b.se) ? a : b;
}

pair<pii, double> stripClosest(vector<Point>& strip, double d) {
    double mn = d;
    pii ret = {-1, -1};
    sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });
    int sz = strip.size();
    for(int i = 0; i < sz; ++i) {
        for(int j = i + 1; j < sz && (strip[j].y - strip[i].y) < mn; ++j) {
            double cur = dist(strip[i], strip[j]);
            if(cur < mn) {
                ret = {strip[i].id, strip[j].id};
                mn = cur;
            }
        }
    }
    return {ret, mn};
}

pair<pii, double> closestUtil(Point P[], int n) {
    if(n <= 3) return bruteForce(P, n);
    int mid = n / 2;
    Point midPoint = P[mid];
    pair<pii, double> dl = closestUtil(P, mid);
    pair<pii, double> dr = closestUtil(P + mid, n - mid);
    pair<pii, double> d = getmin(dl, dr);

    vector<Point> strip;
    for(int i = 0; i < n; i++) {
        if(abs(P[i].x - midPoint.x) < d.second)
            strip.push_back(P[i]);
    }
    return getmin(d, stripClosest(strip, d.second));
}

pair<pii, double> closest(Point P[], int n) {
    sort(P, P + n, [](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    return closestUtil(P, n);
}
