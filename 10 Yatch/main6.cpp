#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <tuple>

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

void print(const  vector<vector<tuple<int, vector<int>, vector<int>>>>& vvpivi) {
    cout << '\n';
    for (const vector<tuple<int, vector<int>, vector<int>>>& vpivi : vvpivi) {
        for (const tuple<int, vector<int>, vector<int>>& pivi : vpivi) {
            printf("%7d ", get<0>(pivi));
        }
        cout << '\n';
    }
}

int main() {
    int N; cin >> N;

    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end(), compare);

    vector<vector<tuple<int, vector<int>, vector<int>>>> dp (N + 1, vector<tuple<int, vector<int>, vector<int>>> (N + 1, tuple<int, vector<int>, vector<int>> (0, vector<int> (N + 1), vector<int>())));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < i; j++) {
            if (get<0>(dp[i - 1][j]) == INF) {
                get<0>(dp[i][j]) = INF;
                continue;
            }

            int min_idx = 0;
            int skipCount = 0;
            for (int k = 0; k < i - 1; k++) {
                if (get<1>(dp[i - 1][k])[j] > 1 || get<0>(dp[i - 1][k]) == INF) {skipCount++; continue;}
                if (get<0>(dp[i - 1][k]) <= get<0>(dp[i - 1][min_idx])) min_idx = k;
            }

            if (skipCount == i - 1 && i > 1) get<0>(dp[i][j]) = INF;
            else {
                get<0>(dp[i][j]) = get<0>(dp[i - 1][min_idx]) + d(points[i], points[j]);
                get<1>(dp[i][j]) = get<1>(dp[i - 1][min_idx]); 
                get<1>(dp[i][j])[i]++; 
                get<1>(dp[i][j])[j]++;
                get<2>(dp[i][j]) = get<2>(dp[i - 1][min_idx]);
                get<2>(dp[i][j]).push_back(j);
            }
        }
    }

    print(dp);

    int min_dist = INF;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (get<0>(dp[N][i]) == INF) continue;
            if (get<1>(dp[N][i])[j] == 1) {
                printf("%d ", get<0>(dp[N][i]) + d(points[N], points[j]));
                min_dist = min(min_dist, get<0>(dp[N][i]) + d(points[N], points[j]));
                break;
            }
        }
    }
    printf("\n\n");

    for (int i = 0; i < N; i++) {
        if (get<0>(dp[N][i]) == INF) for (int j = 0; j < N; j++) printf("%d ", 9);
        else for (int j = 0; j < N; j++) printf("%d ", get<2>(dp[N][i])[j]);
        printf("   ");
    }

    cout << '\n' << min_dist << '\n';

    return 0;
}