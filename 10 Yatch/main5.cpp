#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

#define INF 1000000

using namespace std;

vector<pair<int, int>> points = {{0, 500}};

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

int d(const pair<int, int>& a, const pair<int, int>& b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return sqrt(dx*dx + dy*dy);
}

void print(const  vector<vector<pair<int, vector<int>>>>& vvpivi) {
    cout << '\n';
    for (const vector<pair<int, vector<int>>>& vpivi : vvpivi) {
        for (const pair<int, vector<int>>& pivi : vpivi) {
            for (int i : pivi.second) {
                cout << i << " ";
            }
            cout << "   ";
        }
        cout << '\n';
    }
    cout << '\n';

    cout << '\n';
    for (const vector<pair<int, vector<int>>>& vpivi : vvpivi) {
        for (const pair<int, vector<int>>& pivi : vpivi) {
            cout << pivi.first << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    int N; cin >> N;

    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end(), compare);

    vector<vector<pair<int, vector<int>>>> dp (N + 1, vector<pair<int, vector<int>>> (N + 1, pair<int, vector<int>> (0, vector<int> (N + 1))));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[i - 1][j].first == INF) {
                dp[i][j].first = INF;
                continue;
            }
            int min_idx = 0;
            bool nextExists = false;
            for (int k = 0; k < i - 1; k++) {
                if (dp[i - 1][k].second[j] > 1) continue;
                if (dp[i - 1][k].first <= dp[i - 1][min_idx].first) min_idx = k, nextExists = true;
            }
            if (nextExists == false && i > 1) dp[i][j].first = INF;
            else {
                dp[i][j].first = dp[i - 1][min_idx].first + d(points[i], points[j]);
                dp[i][j].second = dp[i - 1][min_idx].second; 
                dp[i][j].second[i]++; 
                dp[i][j].second[j]++;
            }
        }
    }

    print(dp);

    int min_dist = INF;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dp[N][i].first == INF) continue;
            if (dp[N][i].second[j] == 1) {
                // printf("%d ", dp[N][i].first + d(points[N], points[j]));
                min_dist = min(min_dist, dp[N][i].first + d(points[N], points[j]));
                break;
            }
        }
    }

    cout << min_dist << '\n';

    return 0;
}