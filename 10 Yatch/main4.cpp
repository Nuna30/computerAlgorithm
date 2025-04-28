#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>
#include <cmath>

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

int minDist = INT_MAX;
vector<int> degree (100, 0);
void DFS(int p, int dist) {
    if (p == points.size() - 1) {
        for (int i = p - 1; i >=0; i--) {
            if (degree[i] == 2) continue;
            dist += d(points[p], points[i]);
        }
        minDist = min(minDist, dist);
        return;
    }

    for (int i = p - 1; i >= 0; i--) {
        if (degree[i] == 2) continue;
        degree[i]++;
        degree[p]++;
        DFS(p + 1, dist + d(points[p], points[i]));
        degree[i]--;
        degree[p]--;
    }
}

int main() {
    int N; cin >> N;

    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end(), compare);

    DFS(1, 0);

    cout << minDist;

    return 0;
}