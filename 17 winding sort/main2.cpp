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

double calcDistance(const point& p, const point& q) {
    return sqrt((q.y - p.y) * (q.y - p.y) + (q.x - p.x) * (q.x - p.x));
}

int crossProduct(const point& p, const point& q, const point& s) {
    return (q.x - p.x) * (s.y - p.y) - (q.y - p.y) * (s.x - p.x);
}

bool signed_area(const point& p, const point& q, set<point>& S) {
    int positiveSign = 0;
    int negativeSign = 0;
    for (const point& s : S) {
        if (p.idx == s.idx || q.idx == s.idx) continue;
        int cross = crossProduct(p, q, s);
        if (cross > 0) positiveSign++;
        else if (cross < 0) {
            negativeSign++;
            // if (q.idx == 2) printf("\npi, qi, si : %d, %d, %d\n", p.idx, q.idx, s.idx);
        }
    }
    if (q.idx == 2) {
        // cout << "sign : " << positiveSign << " " << negativeSign << endl;
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
        vector<pair<double, point>> candidates;
        for (const point& q : S) {
            if (signed_area(p, q, S)) {
                double rad = atan2(q.y - p.y, q.x - p.x);
                double ang = rad * 180 / PI;
                if (ang < 0) ang += 360;
                candidates.push_back({ang, q});
                printf("idx, ang : %d, %.2lf\n", q.idx, ang);
            }
        }
        cout << '\n';
        if (candidates.size() == 0) return 1;
        auto& [min_ang, min_point] = candidates[0];
        if (candidates.size() > 1) {
            bool lab = false;
            for (int i = 1; i < candidates.size(); i++) {
                const auto& [ang, q] = candidates[i];
                if (crossProduct(p, min_point, q) == 0) {
                    if (calcDistance(p, q) < calcDistance(p, min_point)) {
                        printf("#1 p : %d, %d -> %d\n", p.idx, min_point.idx, q.idx);
                        min_ang = ang;
                        min_point = q;
                        lab = true;
                    }
                }
                else if (ang >= pa && ang < min_ang) {
                    printf("#2 p: %d, %d -> %d\n", p.idx, min_point.idx, q.idx);
                    min_ang = ang;
                    min_point = q;
                    lab = true;
                } 
            }
            if (lab == false) {
                for (int i = 1; i < candidates.size(); i++) {
                    const auto& [ang, q] = candidates[i];
                    if (crossProduct(p, min_point, q) == 0) {
                        if (calcDistance(p, q) < calcDistance(p, min_point)) {
                            min_ang = ang;
                            min_point = q;
                            lab = true;
                        }
                    }
                    else if (ang > pa && ang < min_ang) {
                        min_ang = ang;
                        min_point = q;
                        lab = true;
                    } 
                }
            }
        }
        cout << min_point.idx << endl;
        p = min_point;
        pa = min_ang;
        S.erase(p);
    }
    for (const point& q : S) cout << q.idx << endl;

    return 0;
}