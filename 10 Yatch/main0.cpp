#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void print(vector<pair<int, int>> vpii) {
    for (auto i : vpii) {
        printf("{%d, %d} ", i.first, i.second);
    }
    printf("\n");
}

void pritn(vector<int> vi) {
    for (int i : vi) cout << i << " ";
    cout << '\n';
}

void print(vector<vector<int>> vvi) {
    for (vector<int> vi : vvi) {
        for (int i : vi) cout << i << " ";
        cout << '\n';
    }
    cout << '\n';
}

bool compare(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first < b.first;
}

int calc_distance(pair<int, int> a, pair<int, int> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

vector<pair<int, int>> points = {{0, 500}};

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
void sailing(int s, int e) {
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
    for (vector<int> route : routes) {
        double distanceSum = 0;
        pair<int, int> startPoint = points[route[0]];
        printf("{%d, %d}--", startPoint.first, startPoint.second);
        for (int i = 1; i < route.size(); i++) {
            pair<int, int> nextPoint = points[route[i]];
            distanceSum += calc_distance(startPoint, nextPoint);
            printf("%6.3f--{%2d,%2d}--", calc_distance(startPoint, nextPoint), nextPoint.first, nextPoint.second);
            startPoint = nextPoint;
        }
        printf("[%3.3f]\n", distanceSum);
    }
}

int main() {
    // points = {{0, 0}, {1, -1}, {2, 2}, {3, -1}, {4, 0}};
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end(), compare);
    sailing(0, N);
    
    

    return 0;
}