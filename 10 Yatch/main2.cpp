#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>
#include <cmath>

using namespace std;

vector<pair<int, int>> points = {{-1, -1}, {0, 500}};

bool compare(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

int calc_distance(pair<int, int> a, pair<int, int> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

vector<int> dp;

int main() {
    int N; cin >> N;

    dp.resize(N + 2, INT_MAX); // dp[i]는 i번째 점이 삽입 되었을 때 최소값, {0, 500}이 1번째 점

    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end(), compare);

    dp[3] = calc_distance(points[1], points[2]) + calc_distance(points[2], points[3]) + calc_distance(points[3], points[1]);

    for (int i = 4; i < dp.size(); i++) {
        for (int j = i; j > 3; j--) {
            int line1 = calc_distance(points[j], points[j - 1]);
            int line2 = calc_distance(points[j], points[j - 2]);
            int line3 = calc_distance(points[j], points[j - 3]);
            int line4 = calc_distance(points[j - 1], points[j - 2]);
            int line5 = calc_distance(points[j - 1], points[j - 3]);
            dp[i] = min(dp[i], min(dp[j - 1] + line1 + line2 - line4, dp[j - 1] + line1 + line3 - line5));
            cout << dp[i] << " ";
        }
    }

    cout << dp[N + 1];

    return 0;
}