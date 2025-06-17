#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double PI = acos(-1.0);

struct Circle {
    double x;
    double y;
    double r;
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

    printf("d %.2lf, area1 %.2lf, area2 %.2lf, sector1_area %.2lf, sector2_area %.2lf, triangle1_area %.2lf, triangle2_area %.2lf\n", d, area1, area2, sector1_area, sector2_area, triangle1_area, triangle2_area);

    if      (d >= c1.r + c2.r)  {
        cout << "#1" << endl;
        return 0.0; 
    }
    else if (d + c1.r <= c2.r)  {
        cout << "#2" << endl;
        return area1;
    }
    else if (d + c2.r <= c1.r)  {
        cout << "#3" << endl;
        return area2;
    }
    else if (d < c1.r)          {
        cout << "#4" << endl;
        return (area2 - sector2_area) + (sector1_area - triangle1_area) + triangle1_area;
    }
    else if (d < c2.r)          {
        cout << "#5" << endl;
        return (area1 - sector1_area) + (sector2_area - triangle2_area) + triangle2_area;
    }
    else                        {
        cout << "#6" << endl;
        return sector1_area + sector2_area - triangle1_area - triangle2_area;
    }
}

int main() {
    // int N; cin >> N;

    vector<Circle> circles;

    circles.push_back({0, 0, 3});

    for (double x = 6; x >= 0; x -= 0.5) {
        circles.push_back({x, 0, 3});
    }

    int N = circles.size();
    double idx1, idx2;
    double maxOverlappingArea = 0;
    for (int j = 1; j < N; j++) {
        double overlappingArea = calc_overlappingArea(circles[0], circles[j]);
        cout << circles[0].x << " " << circles[j].x << "     " << overlappingArea << endl << endl;
        if (overlappingArea > maxOverlappingArea) {
            maxOverlappingArea = overlappingArea;
        }
    }


    cout << idx1 + 1 << " " << idx2 + 1<< endl;

    return 0;
}