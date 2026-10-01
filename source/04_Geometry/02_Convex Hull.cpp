// Andrew's Monotone Chain untuk mencari Convex Hull 2D dan Winding Number untuk point-in-polygon test.
// Convex Hull O(N log N), Point in Polygon O(N).
typedef long double TD;
namespace GEOM {
    typedef pair<TD, TD> Pt;
    const TD EPS = 1e-9;

    TD cross(Pt o, Pt a, Pt b) {
        return (a.first - o.first) * (b.second - o.second) -
               (a.second - o.second) * (b.first - o.first);
    }

    TD cross(Pt a, Pt b) {
        return a.first * b.second - a.second * b.first;
    }

    TD dist(Pt a, Pt b) {
        return hypot(a.first - b.first, a.second - b.second);
    }

    TD shoelaceX2(const vector<Pt>& convHull) {
        TD ret = 0;
        int n = convHull.size();
        for(int i = 0; i < n; i++)
            ret += cross(convHull[i], convHull[(i + 1) % n]);
        return fabs(ret);
    }

    vector<Pt> createConvexHull(vector<Pt> pts) {
        int n = pts.size(), k = 0;
        if(n <= 2) return pts;
        vector<Pt> h(2 * n);
        sort(pts.begin(), pts.end());

        for(int i = 0; i < n; ++i) {
            while(k >= 2 && cross(h[k - 2], h[k - 1], pts[i]) <= 0)
                k--;
            h[k++] = pts[i];
        }

        for(int i = n - 2, t = k + 1; i >= 0; i--) {
            while(k >= t && cross(h[k - 2], h[k - 1], pts[i]) <= 0)
                k--;
            h[k++] = pts[i];
        }
        h.resize(k - 1);
        return h;
    }

    bool isInside(Pt pv, const vector<Pt>& x) {
        int n = x.size(), wn = 0;
        for(int i = 0; i < n; ++i) {
            Pt cur = x[i], nxt = x[(i + 1) % n];
            if(cur.second <= pv.second) {
                if(nxt.second > pv.second && cross(cur, nxt, pv) > 0)
                    ++wn;
            } else if(nxt.second <= pv.second && cross(cur, nxt, pv) < 0) {
                --wn;
            }
        }
        return wn != 0;
    }
}
