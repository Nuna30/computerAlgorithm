#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);

int main() {
    vector<double> vx = {1, 1, -1, -1, 1};
    vector<double> vy = {0, 1, 1, -1, -1};

    for (int i = 0; i < 5; i++) {
        double a = atan2(vy[i], vx[i]) * 180 / PI;
        for (int j = 0; j < 5; j++) {
            double b = atan2(vy[j], vx[j]) * 180 / PI;
            cout << b - a << endl;
        }
        cout << endl;
    }

    return 0;
}