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
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return idx < other.idx;
    }
} point;

이 부분 cross product를 사용해서 부호 판단하는 걸로 개선
현재 06.inp 빼고 다 통과됨
그리고 같은 직선 상에 있을 때 거리가 짧은 점을 택하는 로직 없음

bool signed_area(const point& p, const point& q, set<point>& S) {
    double a = double(q.y - p.y) / (q.x - p.x);
    double b = p.y - a * p.x;

    int sign = 0;
    int prev_sign = 0;
    for (const point& s : S) {
        if (s.idx == p.idx || s.idx == q.idx) continue;
        double compare = s.y - a * s.x - b;
        if (compare == 0) continue;
        prev_sign = sign;
        sign = ((compare > 0) ? 1 : -1);
        if (prev_sign != 0 && sign != prev_sign) return false;
    }
    return true;
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