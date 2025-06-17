#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double PI = acos(-1.0);

struct Circle {
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
    double angle1           = 2 * acos((c1.r*c1.r + d*d - c2.r*c2.r)/(2*d*c1.r));
    double angle2           = 2 * acos((c2.r*c2.r + d*d - c1.r*c1.r)/(2*d*c2.r));
    double sector1_area     = c1.r * c1.r * angle1 * 0.5;
    double sector2_area     = c2.r * c2.r * angle2 * 0.5;
    double triangle1_area   = c1.r * c1.r * sin(angle1) * 0.5;
    double triangle2_area   = c2.r * c2.r * sin(angle2) * 0.5;

    if      (d > c1.r + c2.r )  return 0.0; 
    else if (d + c1.r <= c2.r)  return area1;
    else if (d + c2.r <= c1.r)  return area2;
    else if (d < c1.r)          return (area2 - sector2_area) + (sector1_area - triangle1_area) + triangle1_area;
    else if (d < c2.r)          return (area1 - sector1_area) + (sector2_area - triangle2_area) + triangle2_area;
    else                        return sector1_area + sector2_area - triangle1_area - triangle2_area;
}

int main() {
    int N; cin >> N;

    vector<Circle> circles;

    for (int i = 0; i < N; i++) {
        int idx, x, y, r; cin >> idx >> x >> y >> r;
        circles.push_back({x, y, r});
    }

    double idx1, idx2;
    double maxOverlappingArea = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double overlappingArea = calc_overlappingArea(circles[i], circles[j]);
            // cout << overlappingArea << endl;
            if (overlappingArea > maxOverlappingArea) {
                maxOverlappingArea = overlappingArea;
                idx1 = i, idx2 = j;
            }
        }
    }

    cout << idx1 + 1 << " " << idx2 + 1<< endl;

    return 0;
}