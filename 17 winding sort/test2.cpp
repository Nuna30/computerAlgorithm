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
    
    double px = 0, py = 0, pd = 0;
    vector<int> vi = {12, 14, 2, 6, 3, 7, 11, 8, 1, 4, 10, 13, 9, 5};
    for (int i = 0; i < N; i++) {
        int idx = vi[i];
        double x = vx[idx - 1];
        double y = vy[idx - 1];

        // double tan8 = abs((m1 - m2) / (1 - m1*m2));
        double d = atan2((y - py), (x - px)) * 180 / PI;
        if (d < 0) d += 360;
        double r = d - pd;
        // if (d > 270 && pd > 270) r += 180;
        if (r < 0) r += 360;
        printf("%d : (%.0f, %.0f), %.2lf, %.2lf, %.2lf\n", idx, x, y, d, pd, r);

        px = x;
        py = y;
        pd = d;
    }
}