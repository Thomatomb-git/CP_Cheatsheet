// Algoritma/Fungsi: Sutherland-Hodgman Polygon Clipping untuk memotong poligon terhadap poligon konveks/half-plane.
// Kompleksitas Waktu: O(N * M) dengan N titik poligon dan M titik pemotong.
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct point {
    double x, y;
    point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
};

struct vec {
    double x, y;
    vec(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    vec(point a, point b) : x(b.x - a.x), y(b.y - a.y) {}
};

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }
bool ccw(point p, point q, point r) { return cross(vec(p, q), vec(p, r)) > EPS; }

point intersect(point s1, point e1, point s2, point e2) {
    double num1 = (s1.x * e1.y - s1.y * e1.x) * (s2.x - e2.x) - (s1.x - e1.x) * (s2.x * e2.y - s2.y * e2.x);
    double num2 = (s1.x * e1.y - s1.y * e1.x) * (s2.y - e2.y) - (s1.y - e1.y) * (s2.x * e2.y - s2.y * e2.x);
    double den = (s1.x - e1.x) * (s2.y - e2.y) - (s1.y - e1.y) * (s2.x - e2.x);
    return point(num1 / den, num2 / den);
}

void clip(vector<point>& poly_points, point p1, point p2) {
    vector<point> new_points;
    int n = poly_points.size();
    for(int i = 0; i < n; i++) {
        int k = (i + 1) % n;
        bool i_in = cross(vec(p1, p2), vec(p1, poly_points[i])) >= -EPS;
        bool k_in = cross(vec(p1, p2), vec(p1, poly_points[k])) >= -EPS;
        if(i_in && k_in)
            new_points.push_back(poly_points[k]);
        else if(!i_in && k_in) {
            new_points.push_back(intersect(p1, p2, poly_points[i], poly_points[k]));
            new_points.push_back(poly_points[k]);
        } else if(i_in && !k_in) {
            new_points.push_back(intersect(p1, p2, poly_points[i], poly_points[k]));
        }
    }
    poly_points = new_points;
}

double area(const vector<point>& p) {
    double res = 0.0;
    int n = p.size();
    for(int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        res += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return fabs(res) / 2.0;
}

void suthHodgClip(vector<point>& poly_points, const vector<point>& clipper_points) {
    int n = clipper_points.size();
    for(int i = 0; i < n; i++) {
        int k = (i + 1) % n;
        clip(poly_points, clipper_points[i], clipper_points[k]);
    }
}
