#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double PI = acos(-1.0);

int main() {
    int N; cin >> N;

    vector<double> vx;
    vector<double> vy;

    for (int i = 0; i < N; i++) {
        int idx;
        double x, y;
        cin >> idx >> x >> y;
        vx.push_back(x);
        vy.push_back(y);
    }
    
    double m1 = 0, px = 0, py = 0;
    double m2;
    vector<int> vi = {12, 14, 2, 6, 3, 7, 11, 8, 1, 4, 10, 13, 9, 5};
    for (int i = 0; i < N; i++) {
        int idx = vi[i];
        double x = vx[idx - 1];
        double y = vy[idx - 1];

        m2 = (y - py) / (x - px);

        double tan8 = abs((m1 - m2) / (1 - m1*m2));
        double betweenDegree = atan(tan8) * 180 / PI;
        printf("%d : (%.0f, %.0f), %.2lf\n", idx, x, y, betweenDegree);

        m1 = m2;
        px = x;
        py = y;
    }
}