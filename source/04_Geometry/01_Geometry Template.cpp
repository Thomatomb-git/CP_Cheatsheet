/*
TABLE OF CONTENT
0. Basic Rule
    0.1. Everything is in double
    0.2. Every comparison use EPS
    0.3. Every degree in rad
1. General Double Operation
    1.1. const double EPS=1E-9
    1.2. const double PI=acos(-1.0)
    1.3. const double INFD=1E9
    1.3. between_d(double x,double l,double r)
        check whether x is between l and r inclusive with EPS
    1.4. same_d(double x,double y)
        check whether x=y with EPS
    1.5. dabs(double x)
        absolute value of x

2. Point
    2.1. struct point
        2.1.1. double x,y
            cartesian coordinate of the point
        2.1.2. point()
            default constructor
        2.1.3. point(double _x,double _y)
            constructor, set the point to (_x,_y)
        2.1.4. bool operator< (point other)
            regular pair<double,double> operator < with EPS
        2.1.5. bool operator== (point other)
            regular pair<double,double> operator == with EPS
    2.2. hypot(point P)
        length of hypotenuse of point P to (0,0)
    2.3. e_dist(point P1,point P2)
        euclidean distance from P1 to P2
    2.4. m_dist(point P1,point P2)
        manhattan distance from P1 to P2
    2.5. pointBetween(point P, point L, point R)
        checkifpointPisinbetweenLandR
    2.6. collinear(point P, point L, point R)
        check if the three points are collinear
    2.7. mid(point P, point Q)
        find mid point of P and Q

3.Vector
    3.1.structvec
        3.1.1. double x, y
            x and y are magnitudes of the vector
        3.1.2. vec()
            defaultconstructor
        3.1.3. vec(double _x, double _y)
            constructor, set the vector to (_x, _y)
        3.1.4. vec(point A, point B)
            constructor, set the vector to vector AB (A->B)
    3.2. scale(vec v, double x)
        scalevectorvbyx
    3.3. flip(vec v)
        flip the direction of v
    3.4. dot(vec u, vec v)
    3.5. cross(vec u, vec v)
    3.6. norm_sq(vec v)
        return length of v

4. Additional Point Operators (needs point and vec)
    4.1. rotate (point P, point O, double angle)
        rotate point P from the origin O by angle (CCW)
    4.2. angle (point A, point O, point B)
        check the angle of AOB
    4.3. orientation (point P, point Q, point R)
        check the orientation of PR towards PQ

5. Line
    5.1. struct line
        5.1.1. double a, b, c
            coefficients of line in ax+by+c=0
        5.1.2. line()
            default constructor
        5.1.3. line (double _a, double _b, double _c)
            makeline_ax+_by+_c=0
        5.1.4. line (point P1, point P2)
            make line that goes through P1 and P2
        5.1.5. line (point P, double slope)
            make line that goes through P and has slope
        5.1.6.bool operator==
        5.1.7.double slope()
            return slope of the line
    5.2. paralel (line L1, line L2)
        check if L1 and L2 are parallel
    5.3. intersection (line L1, line L2, point &P)
        check if L1 and L2 intersects,
        and return the intersection point P
    5.4. pointToLine (point P, point A, point B, point &C)
        return the distance of point P to line AB
        and the projection point C
        note: only needs point and vec
    5.5. lineToLine (line L1, line L2)
        return the distance between L1 and L2

6. Line Segment (needs point and line)
    6.1.structsegment
        6.1.1. point P, Q
            start point and end point
        6.1.2. line L -> line equation
        6.1.3. segment()
            default constructor
        6.1.4. segment (point _P, point _Q)
            make segment from point P to Q
        6.1.5. bool operator==
    6.2. onSegment (point P, segment S)
        check if point P is on segment S
    6.3. s_intersection (segment S1, segment S2)
        check if two segments intersect
    6.4. pointToSegment (point P, point A, point B, point &C)
        return the distance of point P to segment AB
        and the projection point C
    6.5. segmentToSegment(segment S1, segment S2)
        return the distance of two segments
    6.6. lineIntersectSeg (point p, point q, point A, point B)
        assuming they intersect, return the intersection point
        of segment pq and line AB\

7.Circle
    7.1.structcircle
        7.1.1. point P -> center point
        7.1.2. double r -> radius
        7.1.3. circle()
            default constructor
        7.1.4. circle(point _P, double _r)
            make circle with center point P and radius r
        7.1.5. circle (point P1, point P2)
            make circle with diameter P1P2
        7.1.6. circle(point P1, point P2, point P3)
            make circle that pass through P1, P2, and P3
        7.1.7. bool operator==
    7.2. insideCircle (point P, circle C)
        check if point P is inside circle C
    7.3. c_intersection (circle C1, circle C2, point &P1, point &P2)
        check if two circle intersects
        and return the points in P1 and P2
    7.4. lc_intersection (line L, circle O, point &P1, point &P2)
        check if line and circle intersects
        and return the points in P1 and P2
    7.5. sc_intersection (segment S, circle C, point &P1, point &P2)
        check if segment and circle intersects
        and return the points in P1 and P2

8.Triangle
    8.1. t_perimeter (point A, point B, point C)
        return perimeter of triangle
    8.2. t_area (point A, point B, point C)
        return area of triangle
    8.3. t_inCircle (point A, point B, point C)
        return in-circle of the triangle
    8.4. t_outCircle (point A, point B, point C)
        return circum-circle of the triangle

9.Polygon
    9.1. struct polygon
        9.1.1. vector<point> P
            list of points in the polygon
        9.1.2. polygon()
            default constructor
        9.1.3. polygon (const vector<point>& _P)
            make polygon from point list
    9.2. rayCast (point P, polygon &A)
        check if point is inside polygon
    9.3. cutPolygon(point a, point b, const vector<point> &Q)
        cuts polygon Q along the line formed
        by point a and point b
    9.4. minCoverCircle (polygon &A)
        return circle that covers polygon

10. Other Geometry Algorithms
    10.1. minCostPolygonTriangulation(polygon &A)
        return min cost of polygon triangulation
*/
//======================================
//1.General Double Operations
//======================================
#define For(i, a, b) for(int i = (a); i <= (b); ++i)
#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define pb push_back

const double PI = acos(-1.0);
const double INFD = 1E9;
const double EPS = 1e-9;
double between_d(double x, double l, double r){
  return (min(l,r) <= x + EPS && x <= max(l,r) + EPS);
}
double same_d (double x, double y){
  return between_d (x, y, y);
}
double dabs(double x){
  if (x < EPS) return -x;
  return x;
}
//======================================
//2.Point
//======================================
struct point{
  double x, y;
  point() {x = y = 0.0;}
  point(double _x, double _y) : x(_x), y(_y){}
  bool operator< (point other){
    if (x < other.x + EPS) return true;
    if(x + EPS > other.x) return false;
    return y < other.y + EPS;
  }
  bool operator== (point other){
  return same_d(x, other.x) && same_d(y, other.y);
  }
};
double e_dist (point P1, point P2){ 
  return hypot (P1.x - P2.x, P1.y - P2.y);
}
double m_dist(point P1, point P2){
  return dabs(P1.x - P2.x) + dabs(P1.y - P2.y);
}
double pointBetween(point P, point L, point R){
  return(e_dist(L,P) + e_dist(P,R) == e_dist(L,R));
}
bool collinear(point P, point L, point R){
  return dabs(P.x * (L.y - R.y) + L.x * (R.y - P.y)
    + R.x * (P.y - L.y)) < EPS;
}
point mid(point P, point Q){
  return point((P.x + Q.x)/2, (P.y + Q.y)/2);
}
//======================================
//3.Vector
//======================================
struct vec{
  double x, y;
  vec(){x = y = 0.0;}
  vec(double _x, double _y) : x(_x), y(_y){}
  vec(point A) : x(A.x), y(A.y){}
  vec(point A, point B) : x(B.x - A.x), y(B.y - A.y){}
};
vec scale(vec v, double s){
  return vec(v.x * s, v.y * s);
}
vec flip(vec v){
  return vec(-v.x, -v.y);
}
double dot(vec u, vec v){
  return(u.x * v.x + u.y * v.y);
}
double cross(vec u, vec v){
  return(u.x * v.y - u.y * v.x);
}
double norm_sq(vec v){
  return(v.x * v.x + v.y * v.y);
}
//======================================
//4.AdditionalPointOperators
//======================================
point translate(point P, vec v){
  return point(P.x + v.x, P.y + v.y);
}
point rotate(point P, point O, double angle){
  vec v(O);
  P = translate(P, flip(v));
  return translate(point(P.x * cos(angle) - P.y * sin(angle),
    P.x * sin(angle) + P.y * cos(angle)), v);
}
double angle(point A, point O, point B){
  vec OA (O,A), OB (O,B);
  return acos(dot(OA,OB) / sqrt(norm_sq(OA) * norm_sq(OB)));
}
int orientation(point P, point Q, point R){
  vec PQ(P,Q), PR(P,R);
  double c = cross(PQ, PR);
  if (c < -EPS) return -1;
  if(c > EPS) return 1;
  return 0;
}
//======================================
//5.Line
//======================================
struct line{
  double a, b, c;
  line(){a = b = c = 0.0;}
  line(double _a, double _b, double _c) : a(_a), b(_b), c(_c){}
  line(point P1, point P2){
    if (P1 < P2) swap(P1, P2);
    if (same_d(P1.x, P2.x))
      a = 1.0, b = 0.0, c = -P1.x;
    else
      a = -(P1.y - P2.y)/(P1.x - P2.x),
      b = 1.0, c = -(a * P1.x) - P1.y;
  }
  line(point P, double slope){
    if (same_d(slope, INFD))
      a = 1.0, b = 0.0, c = -P.x;
    else
      a= -slope, b = 1.0, c = -(a * P.x) - P.y;
  }
  bool operator==(line other){
    return same_d(a, other.a) && same_d(b, other.b)
    && same_d(c, other.c);
  }
  double slope(){
    if (same_d(b, 0.0))return INFD;
    return -(a/b);
  }
};
bool paralel(line L1, line L2){
  return same_d(L1.a, L2.a) && same_d(L1.b, L2.b);
}
bool intersection(line L1, line L2, point &P){
  if (paralel(L1, L2)) return false;
  P.x = (L2.b*L1.c - L1.b*L2.c) / (L2.a*L1.b - L1.a*L2.b);
  if (same_d(L1.b, 0.0))
    P.y = -(L2.a * P.x + L2.c);
  else
    P.y = -(L1.a * P.x + L1.c);
  return true;
}
double pointToLine(point P, point A, point B, point &C){
  vec AP(A,P), AB(A,B);
  double u = dot(AP,AB) / norm_sq(AB);
  C = translate(A, scale(AB, u));
  return e_dist(P, C);
}
double lineToLine(line L1, line L2){
  if (!paralel(L1,L2)) return 0.0;
  return dabs(L2.c - L1.c) / sqrt(L1.a * L1.a + L1.b * L1.b);
}
//======================================
//6.LineSegment
//======================================
struct segment{
  point P, Q;
  line L;
  segment(){
    point T1;
    P = Q = T1;
    line T2;
    L = T2;
  }
  segment(point _P, point _Q){
    P = _P;
    Q = _Q;
    if (Q < P) swap(P, Q);
    line T(P, Q);
    L = T;
    }
    bool operator== (segment other){
    return P == other.P && Q == other.Q;
  }
};
bool onSegment(point P, segment S){
  if (orientation(S.P, S.Q, P) != 0)
    return false;
  return between_d(P.x, S.P.x, S.Q.x)
    && between_d(P.y, S.P.y, S.Q.y);
}
bool s_intersection(segment S1, segment S2){
  double o1 = orientation(S1.P, S1.Q, S2.P);
  double o2 = orientation(S1.P, S1.Q, S2.Q);
  double o3 = orientation(S2.P, S2.Q, S1.P);
  double o4 = orientation(S2.P, S2.Q, S1.Q);
  if (o1 != o2 && o3 != o4)
    return true;
  if (o1 == 0 && onSegment(S2.P, S1))
    return true;
  if(o2 == 0 && onSegment(S2.Q, S1))
    return true;
  if (o3 == 0 && onSegment(S1.P, S2))
    return  true;
  if (o4 == 0 && onSegment(S1.Q, S2))
    return true;
  return false;
}
double pointToSegment(point P, point A, point B, point &C){
  vec AP(A, P), AB(A, B);
  double u = dot(AP, AB) / norm_sq(AB);
  if (u < EPS){
    C = A;
    return e_dist(P, A);
  }
  if (u + EPS > 1.0){
    C = B;
    return e_dist(P, B);
  }
  return pointToLine(P, A, B, C);
}
double segmentToSegment(segment S1, segment S2){
  if (s_intersection(S1, S2)) return 0.0;
  double ret = INFD;
  point dummy;
  ret = min({ret,
    pointToSegment(S1.P, S2.P, S2.Q, dummy),
    pointToSegment(S1.Q, S2.P, S2.Q, dummy),
    pointToSegment(S2.P, S1.P, S1.Q, dummy),
    pointToSegment(S2.Q, S1.P, S1.Q, dummy)
  });
  return ret;
}
//line segment p-q intersect with line A-B.
//note: Tak boleh berimpitan
point lineIntersectSeg(point p, point q, point A, point B){
  double a = B.y - A.y;
  double b = A.x - B.x;
  double c = B.x * A.y - A.x * B.y;
  double u = fabs(a * p.x + b * p.y + c);
  double v = fabs(a * q.x + b * q.y + c);
  return point((p.x * v + q.x * u) / (u+v),
    (p.y * v + q.y * u)/(u+v));
}
//======================================
//7.Circle
//======================================
struct circle{
  point P;
  double r;
  circle() : P(point()), r(0.0){}
  circle(point _P, double _r) : P(_P), r(_r){}
  circle(point P1, point P2) : P(mid(P1, P2)), r(e_dist(P, P1)){}
  circle(point P1, point P2, point P3){
    vector<point> T;
    T.clear();
    T.pb(P1);
    T.pb(P2);
    T.pb(P3);
    sort(T.begin(),T.end());
    P1 = T[0];
    P2 = T[1];
    P3 = T[2];
    point M1, M2;
    M1 = mid(P1, P2);
    M2 = mid(P2, P3);
    point Q2, Q3;
    Q2 = rotate(P2, P1, PI/2);
    Q3 = rotate(P3, P2, PI/2);
    vec P1Q2(P1,Q2), P2Q3(P2,Q3);
    point M3, M4;
    M3 = translate(M1, P1Q2);
    M4 = translate(M2, P2Q3);
    line L1(M1, M3), L2(M2, M4);
    intersection(L1, L2, P);
    r = e_dist(P,P1);
  }
  bool operator== (circle other){
    return (P == other.P && same_d(r, other.r));
  }
};
bool insideCircle(point P, circle C){
  return e_dist(P, C.P) <= C.r + EPS;
}
bool c_intersection(circle C1, circle C2, point &P1, point &P2){
  double d = e_dist(C1.P, C2.P);
  if (d > C1.r + C2.r){
    return false; //d+EPS kalo butuh
  }
  if (d < dabs(C1.r - C2.r) + EPS) return false;
  double x1 = C1.P.x, y1 = C1.P.y, r1 = C1.r,
    x2 = C2.P.x, y2 = C2.P.y, r2 = C2.r;
  double a = (r1*r1 - r2*r2 + d*d)/(2*d),
    h = sqrt(r1*r1 - a*a);
  point T(x1 + a*(x2 - x1)/d,
    y1 + a*(y2 - y1)/d);
  P1 = point(T.x - h*(y2-y1)/d,
    T.y + h*(x2-x1)/d);
  P2 = point(T.x + h*(y2-y1)/d,
    T.y - h*(x2-x1)/d);
  return true;
}
bool lc_intersection(line L, circle O, point &P1, point &P2){
  double a = L.a, b = L.b, c = L.c, 
    x = O.P.x, y=O.P.y, r=O.r;
  double A = a*a + b*b,
  B = 2*a*b*y - 2*a*c - 2*b*b*x,
  C = b*b*x*x + b*b*y*y - 2*b*c*y+c*c - b*b*r*r;
  double D = B*B - 4*A*C;
  point T1, T2;
  if (same_d(b, 0.0)){
    T1.x = c/a;
    if (dabs(x - T1.x) + EPS > r)
      return false;
    if (same_d(T1.x - r - x, 0.0) || same_d(T1.x + r - x, 0.0)){
      P1 = P2 = point(T1.x, y);
      return true;
    }
    double dx = dabs(T1.x - x), dy = sqrt(r*r - dx*dx);
    P1 = point(T1.x, y - dy);
    P2 = point(T1.x, y + dy);
    return true;
  }
  if (same_d(D, 0.0)){
    T1.x = -B / (2*A);
    T1.y = (c - a*T1.x) / b;
    P1 = P2 = T1;
    return true;
  }
  if (D < EPS) return false;
  D = sqrt(D);
  T1.x = (-B - D) / (2*A);
  T1.y = (c - a*T1.x) / b;
  P1 = T1;
  T2.x = (-B + D) / (2*A);
  T2.y = (c - a*T2.x) / b;
  P2 = T2;
  return true;
}
bool sc_intersection(segment S, circle C, point &P1, point &P2){
  bool cek = lc_intersection(S.L, C, P1, P2);
  if (!cek) return false;
  double x1 = S.P.x, y1 = S.P.y, 
    x2 = S.Q.x, y2 = S.Q.y;
  bool b1 = between_d(P1.x, x1, x2) && between_d(P1.y, y1, y2);
  bool b2 = between_d(P2.x, x1, x2) && between_d(P2.y, y1, y2);
  if (P1 == P2) return b1;
  if (b1 || b2){
    if (!b1) P1 = P2;
    if (!b2) P2 = P1;
    return true;
  }
  return false;
}
//======================================
//8.Triangle
//======================================
double t_perimeter(point A, point B, point C){
  return e_dist(A,B) + e_dist(B,C) + e_dist(C,A);
}
double t_area(point A, point B, point C){
  double s = t_perimeter(A,B,C)/2;
  double ab = e_dist(A,B), bc = e_dist(B,C), ac = e_dist(C,A);
  return sqrt(s*(s-ab)*(s-bc)*(s-ac));
}
circle t_inCircle(point A, point B, point C){
  vector<point> T;
  T.clear();
  T.pb(A);
  T.pb(B);
  T.pb(C);
  sort(T.begin(),T.end());
  A = T[0];
  B = T[1];
  C = T[2];
  double r = t_area(A,B,C) / (t_perimeter(A,B,C)/2);
  double ratio = e_dist(A,B) / e_dist(A,C);
  vec BC(B,C);
  BC = scale(BC, ratio/(1 + ratio));
  point P;
  P = translate(B, BC);
  line AP1(A, P);
  ratio = e_dist(B,A)/e_dist(B,C);
  vec AC(A,C);
  AC = scale(AC,ratio / (1+ratio));
  P = translate(A, AC);
  line BP2(B, P);
  intersection(AP1, BP2, P);
  return circle(P, r);
}
circle t_outCircle(point A, point B, point C){
  return circle(A,B,C);
}
//======================================
//9.Polygon
//======================================
struct polygon{
  vector<point> P;
  polygon(){P.clear();}
  polygon(const vector<point>& _P) : P(_P){}
};
bool rayCast(point P, polygon &A) {
  bool inside = false;
  int n = A.P.size();
  for (int i = 0, j = n - 1; i < n; j = i++) {
    if (((A.P[i].y > P.y) != (A.P[j].y > P.y)) &&
      (P.x < (A.P[j].x - A.P[i].x) * (P.y - A.P[i].y) / (A.P[j].y - A.P[i].y) + A.P[i].x))
      inside = !inside;
  }
  return inside;
}
//(note: the last point must be the same as the first point)
vector<point> cutPolygon(point a, point b, const vector<point> &Q){
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); i++){
    double left1 = cross(vec(a, b), vec(a, Q[i]));
    double left2 = 0;
    if(i != (int)Q.size() - 1)
      left2 = cross(vec(a,b), vec(a, Q[i+1]));
    if(left1 > -EPS)
      P.push_back(Q[i]);
    if(left1 * left2 < -EPS)
      P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());
  return P;
}
circle minCoverCircle(polygon &A){
  vector<point> p = A.P;
  point c;
  circle ret;
  double cr = 0.0;
  int i, j, k;
  c = p[0];
  for(i = 1; i < p.size(); i++){
    if(e_dist(p[i], c) >= cr + EPS){
      c = p[i], cr = 0;
      ret = circle(c, cr);
      for(j = 0; j < i; j++){
        if(e_dist(p[j], c) >= cr + EPS){
          c = mid(p[i], p[j]);
          cr = e_dist(p[i], c);
          ret = circle(c, cr);
          for(k = 0; k < j; k++){
            if (e_dist(p[k], c) >= cr + EPS){
              ret = circle(p[i], p[j], p[k]);
              c = ret.P;
              cr = ret.r;
            }
          }
        }
      }
    }
  }
  return ret;
}
//======================================
//10. Other Geometry Algorithm
//======================================
double DP[110][110];
double minCostPolygonTriangulation(polygon &A){
  if (A.P.size() < 3) return 0;
  For(i, 0, A.P.size()){
    for(int j = 0, k = i; k < A.P.size(); j++, k++){
      if (k < j+2)
        DP[j][k] = 0.0;
      else{
        DP[j][k] = INFD;
        rep(l, j+1, k-1){
          double cost = e_dist(A.P[j], A.P[k])
            + e_dist(A.P[k], A.P[l])
            + e_dist(A.P[l], A.P[j]);
            DP[j][k] = min(DP[j][k], DP[j][l] + DP[l][k] + cost);
        }
      }
    }
  }
  return DP[0][A.P.size() - 1];
}