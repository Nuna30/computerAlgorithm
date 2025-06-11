#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;

const double PI = acos(-1.0);

int main() {
    int N; cin >> N;

    vector<bool> visited (N, false);
    vector<pair<int, int>> points;

    for (int i = 0; i < N; i++) {
        int idx, x, y; cin >> idx >> x >> y;
        points.push_back({x, y});
    }

    
    
    int px = 0, py = 0;
    double pd = 0;
    for (int i = 0; i < N; i++) {

        double min_r = numeric_limits<double>::max();
        double min_d;
        double min_idx;
        double min_dist;

        for (int j = 0; j < N; j++) {
            if (visited[j] == true) continue;
    
            double x = points[j].first;
            double y = points[j].second;
            double dist = sqrt((y - py) * (y - py) + (x - px) * (x - px));
    
            double d = atan2((y - py), (x - px)) * 180 / PI;
            if (d < 0) d += 360;

            double r = d - pd;
            if (r < 0) r += 360;
    
            if (r < min_r || (r == min_r && dist < min_dist)) {
                min_r = r;
                min_d = d;
                min_idx = j;
                min_dist = dist;
            }
        }

        cout << min_idx + 1 << endl;

        visited[min_idx] = true;
        
        px = points[min_idx].first;
        py = points[min_idx].second;
        pd = min_d;
    }

}