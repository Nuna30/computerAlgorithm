#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <set>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);

typedef struct point {
    int idx;
    int x;
    int y;

    bool operator<(const point& other) const {
        return idx < other.idx;
    }
} point;

bool signed_area(const point& p, const point& q, set<point>& S) {
    int positiveSign = 0;
    int negativeSign = 0;
    for (const point& s : S) {
        int crossProduct = (q.x - p.x) * (s.y - p.y) - (q.y - p.y) * (s.x - p.x);
        if (crossProduct > 0) positiveSign++;
        else                  negativeSign++;
    }
    if (positiveSign > 0 && negativeSign > 0) return false;
    else                                      return true;
}

int main() {
    int N; cin >> N;

    vector<bool> visited (N, false);
    set<point> S;

    for (int i = 0; i < N; i++) {
        int idx, x, y; cin >> idx >> x >> y;
        S.insert({idx, x, y});
    }

    point p = {0, 0, 0};
    double pa = 0;
    while (S.size() > 1) {
        pair<int, point> p1, p2, n;
        int count = 0;
        for (const point& q : S) {
            if (signed_area(p, q, S)) {
                double rad = atan2(q.y - p.y, q.x - p.x);
                double ang = rad * 180 / PI;
                if (ang < 0) ang += 360;
                if (count == 0) p1 = {ang, q}, count = 1;
                else p2 = {ang, q}, count = 0;
            }
        }
        if (p1.first - pa < p2.first - pa) n = p1;
        else n = p2;
        int na = n.first;
        point np = n.second;
        cout << np.idx << endl;
        p = np;
        pa = na;
        S.erase(np);
    }
    for (const point& q : S) cout << q.idx << endl;

    return 0;
}