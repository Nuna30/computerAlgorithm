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

int calc_distance(const pair<int, int>& a, const pair<int, int>& b) {
    int ax = a.first, bx = b.first;
    int ay = a.second, by = b.second;
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

vector<vector<int>> backtracked_indices;
vector<int> backtracked_index;
void backtrack(int s, int e, int nr) {
    if (nr == 0) {
        backtracked_indices.push_back(backtracked_index);
        return ;
    }
    for (int i = s + 1; i <= e; i++) {
        backtracked_index.push_back(i);
        backtrack(i, e, nr - 1);
        backtracked_index.pop_back();
    }
}

vector<vector<int>> routes;
int sailing(int s, int e) {
    // 백트래킹 해서 갈 때 거쳐가야할 체크포인트 인덱스 수집
    int nr_checkpoint = e - s - 1;
    vector<bool> visited (nr_checkpoint + 2, false);
    for (int i = 1; i <= nr_checkpoint; i++) {
        backtrack(s, e - 1, i);
    }
    // 수집된 인덱스들로 루트 생성
    for (vector<int> backtracked_index : backtracked_indices) {
        vector<int> route;
        for (int i : backtracked_index) {
            visited[i] = true;
        }
        route.push_back(s);
        for (int i = 1; i <= visited.size() - 2; i++) {
            if (visited[i] == true) route.push_back(i);
        }
        route.push_back(e);
        for (int i = visited.size() - 2; i >= 1; i--) {
            if (visited[i] == false) route.push_back(i);
        }
        route.push_back(s);
        for (int i : backtracked_index) {
            visited[i] = false;
        }
        routes.push_back(route);
    }
    // 루트 기반 거리 계산
    int min = INT_MAX;
    for (vector<int> route : routes) {
        int distanceSum = 0;
        pair<int, int> startPoint = points[route[0]];
        for (int i = 1; i < route.size(); i++) {
            pair<int, int> nextPoint = points[route[i]];
            distanceSum += calc_distance(startPoint, nextPoint);
            startPoint = nextPoint;
        }
        if (distanceSum < min) min = distanceSum;
    }
    return min;
}

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end(), compare);

    cout << sailing(0, N);

    return 0;
}