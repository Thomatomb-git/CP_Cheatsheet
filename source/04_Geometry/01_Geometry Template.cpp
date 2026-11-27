using ll = long long;
using ld = long double;

const ld PI = acosl(-1.0L);
const ld INFD = 1E18;
const ld EPS = 1e-9;

inline bool same_d(ld x, ld y) {
    return fabs(x - y) < EPS;
}

inline bool between_d(ld x, ld l, ld r) {
    return (min(l, r) <= x + EPS && x <= max(l, r) + EPS);
}

inline ld dabs(ld x) {
    return fabs(x);
}

struct point {
    ld x, y;
    point() : x(0.0), y(0.0) {}
    point(ld _x, ld _y) : x(_x), y(_y) {}

    bool operator<(const point& other) const {
        if(fabs(x - other.x) > EPS) return x < other.x;
        return y < other.y - EPS;
    }
    bool operator==(const point& other) const {
        return same_d(x, other.x) && same_d(y, other.y);
    }
};

ld e_dist(point P1, point P2) {
    return hypot(P1.x - P2.x, P1.y - P2.y);
}

ld m_dist(point P1, point P2) {
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
    ld x, y;
    vec() : x(0.0), y(0.0) {}
    vec(ld _x, ld _y) : x(_x), y(_y) {}
    vec(point A) : x(A.x), y(A.y) {}
    vec(point A, point B) : x(B.x - A.x), y(B.y - A.y) {}
};

vec scale(vec v, ld s) { return vec(v.x * s, v.y * s); }
vec flip(vec v) { return vec(-v.x, -v.y); }
ld dot(vec u, vec v) { return (u.x * v.x + u.y * v.y); }
ld cross(vec u, vec v) { return (u.x * v.y - u.y * v.x); }
ld norm_sq(vec v) { return (v.x * v.x + v.y * v.y); }

point translate(point P, vec v) { return point(P.x + v.x, P.y + v.y); }
point rotate(point P, point O, ld angle) {
    vec v(O);
    P = translate(P, flip(v));
    return translate(point(P.x * cos(angle) - P.y * sin(angle),
                           P.x * sin(angle) + P.y * cos(angle)), v);
}

ld angle(point A, point O, point B) {
    vec OA(O, A), OB(O, B);
    return acos(dot(OA, OB) / sqrt(norm_sq(OA) * norm_sq(OB)));
}

ll orientation(point P, point Q, point R) {
    vec PQ(P, Q), PR(P, R);
    ld c = cross(PQ, PR);
    if(c < -EPS) return -1;
    if(c > EPS) return 1;
    return 0;
}

struct line {
    ld a, b, c;
    line() : a(0), b(0), c(0) {}
    line(ld _a, ld _b, ld _c) : a(_a), b(_b), c(_c) {}
    line(point P1, point P2) {
        if(same_d(P1.x, P2.x))
            a = 1.0, b = 0.0, c = -P1.x;
        else
            a = -(P1.y - P2.y) / (P1.x - P2.x),
            b = 1.0, c = -(a * P1.x) - P1.y;
    }
    line(point P, ld slope) {
        if(same_d(slope, INFD))
            a = 1.0, b = 0.0, c = -P.x;
        else
            a = -slope, b = 1.0, c = -(a * P.x) - P.y;
    }
    bool operator==(line other) {
        return same_d(a, other.a) && same_d(b, other.b) && same_d(c, other.c);
    }
    ld slope() {
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

ld pointToLine(point P, point A, point B, point &C) {
    vec AP(A, P), AB(A, B);
    ld u = dot(AP, AB) / norm_sq(AB);
    C = translate(A, scale(AB, u));
    return e_dist(P, C);
}

ld lineToLine(line L1, line L2) {
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
    ll o1 = orientation(S1.P, S1.Q, S2.P);
    ll o2 = orientation(S1.P, S1.Q, S2.Q);
    ll o3 = orientation(S2.P, S2.Q, S1.P);
    ll o4 = orientation(S2.P, S2.Q, S1.Q);
    if(o1 != o2 && o3 != o4) return true;
    if(o1 == 0 && onSegment(S2.P, S1)) return true;
    if(o2 == 0 && onSegment(S2.Q, S1)) return true;
    if(o3 == 0 && onSegment(S1.P, S2)) return true;
    if(o4 == 0 && onSegment(S1.Q, S2)) return true;
    return false;
}

ld pointToSegment(point P, point A, point B, point &C) {
    vec AP(A, P), AB(A, B);
    ld u = dot(AP, AB) / norm_sq(AB);
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

ld segmentToSegment(segment S1, segment S2) {
    if(s_intersection(S1, S2)) return 0.0;
    ld ret = INFD;
    point dummy;
    ret = min({ret,
               pointToSegment(S1.P, S2.P, S2.Q, dummy),
               pointToSegment(S1.Q, S2.P, S2.Q, dummy),
               pointToSegment(S2.P, S1.P, S1.Q, dummy),
               pointToSegment(S2.Q, S1.P, S1.Q, dummy)});
    return ret;
}

point lineIntersectSeg(point p, point q, point A, point B) {
    ld a = B.y - A.y;
    ld b = A.x - B.x;
    ld c = B.x * A.y - A.x * B.y;
    ld u = fabs(a * p.x + b * p.y + c);
    ld v = fabs(a * q.x + b * q.y + c);
    return point((p.x * v + q.x * u) / (u + v),
                 (p.y * v + q.y * u) / (u + v));
}

struct circle {
    point P;
    ld r;
    circle() : P(point()), r(0.0) {}
    circle(point _P, ld _r) : P(_P), r(_r) {}
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

// NOTE: line menggunakan konvensi ax+by+c=0. Fungsi ini mensubstitusi ke persamaan lingkaran.
//       Jika b==0, garis vertikal ditangani terpisah.
bool lc_intersection(line L, circle O, point &P1, point &P2) {
    ld a = L.a, b = L.b, c = L.c;
    ld x = O.P.x, y = O.P.y, r = O.r;
    if(same_d(b, 0.0)) {
        ld px = -c / a;
        if(fabs(x - px) > r + EPS) return false;
        ld dy = sqrt(max((ld)0.0, r * r - (px - x) * (px - x)));
        P1 = point(px, y - dy);
        P2 = point(px, y + dy);
        return true;
    }
    // Substitusi y = (-c - ax) / b ke (x-cx)^2 + (y-cy)^2 = r^2
    ld A = a * a + b * b;
    ld B = 2 * a * c + 2 * a * b * y - 2 * b * b * x;
    ld C = b * b * x * x + c * c + 2 * b * c * y + b * b * y * y - b * b * r * r;
    ld D = B * B - 4 * A * C;
    if(D < -EPS) return false;
    D = sqrt(max((ld)0.0, D));
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
    ll n = A.P.size();
    for(ll i = 0, j = n - 1; i < n; j = i++) {
        if(((A.P[i].y > P.y) != (A.P[j].y > P.y)) &&
           (P.x < (A.P[j].x - A.P[i].x) * (P.y - A.P[i].y) / (A.P[j].y - A.P[i].y) + A.P[i].x))
            inside = !inside;
    }
    return inside;
}

// Return: 1 = inside, 0 = boundary, -1 = outside
ll pointInPolygon(point P, polygon &A) {
    ll n = A.P.size();
    for(ll i = 0; i < n; ++i)
        if(onSegment(P, segment(A.P[i], A.P[(i + 1) % n]))) return 0;
    return rayCast(P, A) ? 1 : -1;
}

ld DP[110][110];
ld minCostPolygonTriangulation(polygon &A) {
    ll n = A.P.size();
    if(n < 3) return 0;
    for(ll i = 0; i < n; ++i) {
        for(ll j = 0, k = i; k < n; ++j, ++k) {
            if(k < j + 2)
                DP[j][k] = 0.0;
            else {
                DP[j][k] = INFD;
                for(ll l = j + 1; l <= k - 1; ++l) {
                    ld cost = e_dist(A.P[j], A.P[k]) + e_dist(A.P[k], A.P[l]) + e_dist(A.P[l], A.P[j]);
                    DP[j][k] = min(DP[j][k], DP[j][l] + DP[l][k] + cost);
                }
            }
        }
    }
    return DP[0][n - 1];
}
