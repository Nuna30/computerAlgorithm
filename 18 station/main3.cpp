#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const double PI = acos(-1.0);

struct Circle {
    int idx;
    int x;
    int y;
    int r;
};

double calc_distance(const Circle& c1, const Circle& c2) {
    return sqrt((c2.x - c1.x) * (c2.x - c1.x) + (c2.y - c1.y) * (c2.y - c1.y));
}

double calc_overlappingArea(const Circle& c1, const Circle& c2) {
    double d                = calc_distance(c1, c2);
    double area1            = c1.r*c1.r*PI;
    double area2            = c2.r*c2.r*PI;
    double angle1           = acos((c1.r*c1.r + d*d - c2.r*c2.r)/(2*d*c1.r));
    double angle2           = acos((c2.r*c2.r + d*d - c1.r*c1.r)/(2*d*c2.r));
    double sector1_area     = c1.r * c1.r * angle1;
    double sector2_area     = c2.r * c2.r * angle2;

    if      (d >= c1.r + c2.r)  return 0.0; 
    else if (d + c1.r <= c2.r)  return area1;
    else if (d + c2.r <= c1.r)  return area2;
    else                        return sector1_area + sector2_area - 0.5*sqrt((-d + c1.r + c2.r) * (d + c1.r - c2.r) * (d - c1.r + c2.r) * (d + c1.r + c2.r));
}

int main() {
    int N; cin >> N;

    vector<Circle> circles;

    for (int i = 0; i < N; i++) {
        int idx, x, y, r; cin >> idx >> x >> y >> r;
        circles.push_back({idx, x, y, r});
    }

    vector<Circle> ascendingXL_circles = circles;
    sort(ascendingXL_circles.begin(), ascendingXL_circles.end(), [](const Circle& c1, const Circle& c2){return c1.x - c1.r < c2.x - c2.r;});

    double idx1, idx2;
    double maxOverlappingArea = 0;
    for (int i = 0; i < N; i++) {
        Circle circle_i = ascendingXL_circles[i];
        for (int j = i + 1; j < N; j++) {
            Circle circle_j = ascendingXL_circles[j];
            if (circle_i.x + circle_i.r <= circle_j.x - circle_j.r) break;
            double overlappingArea = calc_overlappingArea(circle_i, circle_j);
            double cutOverlappingArea = (int)(overlappingArea * 1000) / 1000;
            if (overlappingArea > maxOverlappingArea) {
                maxOverlappingArea = overlappingArea;
                idx1 = circle_i.idx, idx2 = circle_j.idx;
            }
        }
    }

    if (idx1 > idx2)    cout << idx2 << " " << idx1 << endl;
    else                cout << idx1 << " " << idx2 << endl;

    return 0;
}