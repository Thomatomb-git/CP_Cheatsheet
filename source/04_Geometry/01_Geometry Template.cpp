// Algoritma/Fungsi: Template komputasi geometri 2D lengkap (Point, Vector, Line, Segment, Circle, Triangle, Polygon).
// Kompleksitas Waktu: Operasi primitif O(1), Ray Casting & Polygon Clipping O(N), Polygon Triangulation O(N^3).
#include <bits/stdc++.h>
using namespace std;

#define For(i, a, b) for(int i = (a); i <= (b); ++i)
#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define pb push_back

const double PI = acos(-1.0);
const double INFD = 1E18;
const double EPS = 1e-9;

inline bool same_d(double x, double y) {
    return fabs(x - y) < EPS;
}

inline bool between_d(double x, double l, double r) {
    return (min(l, r) <= x + EPS && x <= max(l, r) + EPS);
}

inline double dabs(double x) {
    return fabs(x);
}

struct point {
    double x, y;
    point() : x(0.0), y(0.0) {}
    point(double _x, double _y) : x(_x), y(_y) {}

    bool operator<(const point& other) const {
        if(fabs(x - other.x) > EPS) return x < other.x;
        return y < other.y - EPS;
    }
    bool operator==(const point& other) const {
        return same_d(x, other.x) && same_d(y, other.y);
    }
};

double e_dist(point P1, point P2) {
    return hypot(P1.x - P2.x, P1.y - P2.y);
}

double m_dist(point P1, point P2) {
    return dabs(P1.x - P2.x) + dabs(P1.y - P2.y);
}

bool pointBetween(point P, point L, point R) {
    return fabs(e_dist(L, P) + e_dist(P, R) - e_dist(L, R)) < EPS;
}

bool collinear(point P, point L, point R) {
    return dabs(P.x * (L.y - R.y) + L.x * (R.y - P.y) + R.x * (P.y - L.y)) < EPS;
}

point mid(point P, point Q) {
    return point((P.x + Q.x) / 2, (P.y + Q.y) / 2);
}

struct vec {
    double x, y;
    vec() : x(0.0), y(0.0) {}
    vec(double _x, double _y) : x(_x), y(_y) {}
    vec(point A) : x(A.x), y(A.y) {}
    vec(point A, point B) : x(B.x - A.x), y(B.y - A.y) {}
};

vec scale(vec v, double s) { return vec(v.x * s, v.y * s); }
vec flip(vec v) { return vec(-v.x, -v.y); }
double dot(vec u, vec v) { return (u.x * v.x + u.y * v.y); }
double cross(vec u, vec v) { return (u.x * v.y - u.y * v.x); }
double norm_sq(vec v) { return (v.x * v.x + v.y * v.y); }

point translate(point P, vec v) { return point(P.x + v.x, P.y + v.y); }
point rotate(point P, point O, double angle) {
    vec v(O);
    P = translate(P, flip(v));
    return translate(point(P.x * cos(angle) - P.y * sin(angle),
                           P.x * sin(angle) + P.y * cos(angle)), v);
}

double angle(point A, point O, point B) {
    vec OA(O, A), OB(O, B);
    return acos(dot(OA, OB) / sqrt(norm_sq(OA) * norm_sq(OB)));
}

int orientation(point P, point Q, point R) {
    vec PQ(P, Q), PR(P, R);
    double c = cross(PQ, PR);
    if(c < -EPS) return -1;
    if(c > EPS) return 1;
    return 0;
}

struct line {
    double a, b, c;
    line() : a(0), b(0), c(0) {}
    line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
    line(point P1, point P2) {
        if(same_d(P1.x, P2.x))
            a = 1.0, b = 0.0, c = -P1.x;
        else
            a = -(P1.y - P2.y) / (P1.x - P2.x),
            b = 1.0, c = -(a * P1.x) - P1.y;
    }
    line(point P, double slope) {
        if(same_d(slope, INFD))
            a = 1.0, b = 0.0, c = -P.x;
        else
            a = -slope, b = 1.0, c = -(a * P.x) - P.y;
    }
    bool operator==(line other) {
        return same_d(a, other.a) && same_d(b, other.b) && same_d(c, other.c);
    }
    double slope() {
        if(same_d(b, 0.0)) return INFD;
        return -(a / b);
    }
};

bool paralel(line L1, line L2) {
    return same_d(L1.a * L2.b, L1.b * L2.a);
}

bool intersection(line L1, line L2, point &P) {
    if(paralel(L1, L2)) return false;
    P.x = (L2.b * L1.c - L1.b * L2.c) / (L2.a * L1.b - L1.a * L2.b);
    if(same_d(L1.b, 0.0))
        P.y = -(L2.a * P.x + L2.c) / L2.b;
    else
        P.y = -(L1.a * P.x + L1.c) / L1.b;
    return true;
}

double pointToLine(point P, point A, point B, point &C) {
    vec AP(A, P), AB(A, B);
    double u = dot(AP, AB) / norm_sq(AB);
    C = translate(A, scale(AB, u));
    return e_dist(P, C);
}

double lineToLine(line L1, line L2) {
    if(!paralel(L1, L2)) return 0.0;
    return dabs(L2.c - L1.c) / sqrt(L1.a * L1.a + L1.b * L1.b);
}

struct segment {
    point P, Q;
    line L;
    segment() : P(point()), Q(point()), L(line()) {}
    segment(point _P, point _Q) : P(_P), Q(_Q), L(line(_P, _Q)) {}
    bool operator==(segment other) {
        return P == other.P && Q == other.Q;
    }
};

bool onSegment(point P, segment S) {
    if(orientation(S.P, S.Q, P) != 0) return false;
    return between_d(P.x, S.P.x, S.Q.x) && between_d(P.y, S.P.y, S.Q.y);
}

bool s_intersection(segment S1, segment S2) {
    double o1 = orientation(S1.P, S1.Q, S2.P);
    double o2 = orientation(S1.P, S1.Q, S2.Q);
    double o3 = orientation(S2.P, S2.Q, S1.P);
    double o4 = orientation(S2.P, S2.Q, S1.Q);
    if(o1 != o2 && o3 != o4) return true;
    if(o1 == 0 && onSegment(S2.P, S1)) return true;
    if(o2 == 0 && onSegment(S2.Q, S1)) return true;
    if(o3 == 0 && onSegment(S1.P, S2)) return true;
    if(o4 == 0 && onSegment(S1.Q, S2)) return true;
    return false;
}

double pointToSegment(point P, point A, point B, point &C) {
    vec AP(A, P), AB(A, B);
    double u = dot(AP, AB) / norm_sq(AB);
    if(u < EPS) {
        C = A;
        return e_dist(P, A);
    }
    if(u + EPS > 1.0) {
        C = B;
        return e_dist(P, B);
    }
    return pointToLine(P, A, B, C);
}

double segmentToSegment(segment S1, segment S2) {
    if(s_intersection(S1, S2)) return 0.0;
    double ret = INFD;
    point dummy;
    ret = min({ret,
               pointToSegment(S1.P, S2.P, S2.Q, dummy),
               pointToSegment(S1.Q, S2.P, S2.Q, dummy),
               pointToSegment(S2.P, S1.P, S1.Q, dummy),
               pointToSegment(S2.Q, S1.P, S1.Q, dummy)});
    return ret;
}

point lineIntersectSeg(point p, point q, point A, point B) {
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = B.x * A.y - A.x * B.y;
    double u = fabs(a * p.x + b * p.y + c);
    double v = fabs(a * q.x + b * q.y + c);
    return point((p.x * v + q.x * u) / (u + v),
                 (p.y * v + q.y * u) / (u + v));
}

struct circle {
    point P;
    double r;
    circle() : P(point()), r(0.0) {}
    circle(point _P, double _r) : P(_P), r(_r) {}
    circle(point P1, point P2) : P(mid(P1, P2)), r(e_dist(P, P1)) {}
    circle(point P1, point P2, point P3) {
        point M1 = mid(P1, P2), M2 = mid(P2, P3);
        point Q2 = rotate(P2, P1, PI / 2), Q3 = rotate(P3, P2, PI / 2);
        vec P1Q2(P1, Q2), P2Q3(P2, Q3);
        point M3 = translate(M1, P1Q2), M4 = translate(M2, P2Q3);
        line L1(M1, M3), L2(M2, M4);
        intersection(L1, L2, P);
        r = e_dist(P, P1);
    }
    bool operator==(circle other) {
        return P == other.P && same_d(r, other.r);
    }
};

bool insideCircle(point P, circle C) {
    return e_dist(P, C.P) <= C.r + EPS;
}

bool lc_intersection(line L, circle O, point &P1, point &P2) {
    double a = L.a, b = L.b, c = L.c;
    double x = O.P.x, y = O.P.y, r = O.r;
    if(same_d(b, 0.0)) {
        double px = -c / a;
        if(fabs(x - px) > r + EPS) return false;
        double dy = sqrt(max(0.0, r * r - (px - x) * (px - x)));
        P1 = point(px, y - dy);
        P2 = point(px, y + dy);
        return true;
    }
    double A = a * a + b * b;
    double B = 2 * a * b * y - 2 * a * c - 2 * b * b * x;
    double C = b * b * x * x + b * b * y * y - 2 * b * c * y + c * c - b * b * r * r;
    double D = B * B - 4 * A * C;
    if(D < -EPS) return false;
    D = sqrt(max(0.0, D));
    P1.x = (-B - D) / (2 * A);
    P1.y = (-c - a * P1.x) / b;
    P2.x = (-B + D) / (2 * A);
    P2.y = (-c - a * P2.x) / b;
    return true;
}

struct polygon {
    vector<point> P;
    polygon() { P.clear(); }
    polygon(const vector<point>& _P) : P(_P) {}
};

bool rayCast(point P, polygon &A) {
    bool inside = false;
    int n = A.P.size();
    for(int i = 0, j = n - 1; i < n; j = i++) {
        if(((A.P[i].y > P.y) != (A.P[j].y > P.y)) &&
           (P.x < (A.P[j].x - A.P[i].x) * (P.y - A.P[i].y) / (A.P[j].y - A.P[i].y) + A.P[i].x))
            inside = !inside;
    }
    return inside;
}

double DP[110][110];
double minCostPolygonTriangulation(polygon &A) {
    if(A.P.size() < 3) return 0;
    For(i, 0, (int)A.P.size()) {
        for(int j = 0, k = i; k < (int)A.P.size(); j++, k++) {
            if(k < j + 2)
                DP[j][k] = 0.0;
            else {
                DP[j][k] = INFD;
                rep(l, j + 1, k - 1) {
                    double cost = e_dist(A.P[j], A.P[k]) + e_dist(A.P[k], A.P[l]) + e_dist(A.P[l], A.P[j]);
                    DP[j][k] = min(DP[j][k], DP[j][l] + DP[l][k] + cost);
                }
            }
        }
    }
    return DP[0][A.P.size() - 1];
}
