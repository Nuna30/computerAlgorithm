#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

int distance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return (int)sqrt(dx * dx + dy * dy); // 정수 부분만 반환
}

int main() {
    int N;
    cin >> N;

    vector<Point> points;
    points.emplace_back(0, 500); // 시작점 S

    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    // x 좌표 기준으로 정렬
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });

    // DP 테이블 초기화: dp[i][j] = 오른쪽은 i, 왼쪽은 j까지 방문한 최소 거리
    vector<vector<int>> dp(N + 1, vector<int>(N + 1, INT_MAX));
    dp[0][0] = 0; // 시작점 S에서 출발

    for (int k = 1; k <= N; ++k) {
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                if (dp[i][j] == INT_MAX) continue;

                // Case 1: k를 오른쪽 경로에 추가 (i → k)
                int dist_right = distance(points[i], points[k]);
                if (dp[k][j] > dp[i][j] + dist_right) {
                    dp[k][j] = dp[i][j] + dist_right;
                }

                // Case 2: k를 왼쪽 경로에 추가 (j → k)
                int dist_left = distance(points[j], points[k]);
                if (dp[i][k] > dp[i][j] + dist_left) {
                    dp[i][k] = dp[i][j] + dist_left;
                }
            }
        }
    }

    // 최종 경로 완성: t에서 S로 돌아오는 거리 추가
    int min_distance = INT_MAX;
    for (int j = 0; j <= N; ++j) {
        if (dp[N][j] != INT_MAX) {
            int final_dist = dp[N][j] + distance(points[N], points[j]);
            if (final_dist < min_distance) {
                min_distance = final_dist;
            }
        }
    }

    cout << min_distance << endl;

    return 0;
}