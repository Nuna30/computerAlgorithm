#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<pair<int, int>>  coords;

vector<bool>            visited;
vector<vector<int>>     graph;

vector<int>             cycle;
vector<vector<int>>     cycles;

int calcDist(int v1, int v2) {
    const auto& [x1, y1] = coords[v1];
    const auto& [x2, y2] = coords[v2];

    return floor(sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));
}

void print_cycle(const vector<int>& cycle) {
    for (int i : cycle) cout << i << " " ;
    cout << '\n';
}

void DFS(int pv, int v, int depth, int dist) {
    // 42km 이상인 경로는 cut
    if (dist >= 42) {
        // if (dist == 42) cycles.push_back(cycle), print_cycle(cycle);
        if (dist == 42 && v == 0) cycles.push_back(cycle);
        return;
    }

    for (int i = 0; i < graph[v].size(); i++) {
        int next = graph[v][i];
        if (visited[next]) continue;
        if (pv == next) continue;
        visited[next] = true;
        cycle.push_back(next);
        // dist에 거리가 계속 중첩됨됨
        DFS(v, next, depth + 1, dist + calcDist(v, next));
        cycle.pop_back();
        visited[next] = false;
    }
}

struct compare {
    bool operator()(const vector<int>& c1, const vector<int>& c2) {
        if (c1.size() == c2.size()) {
            int maxDist1 = 0;
            int maxDist2 = 0;
            for (int i = 1; i < c1.size(); i++) {
                maxDist1 = max(maxDist1, calcDist(c1[i - 1], c1[i]));
                maxDist2 = max(maxDist2, calcDist(c2[i - 1], c2[i]));
            }
            if (maxDist1 == maxDist2) {
                return c1 < c2;
            }
            return maxDist1 < maxDist2;
        }
        return c1.size() > c2.size();
    }
};

int main() {
    int N; cin >> N;
    graph.resize(N, {});
    visited.resize(N, false);

    for (int i = 0; i < N; i++) {
        int idx, x, y; cin >> i >> x >> y;
        coords.push_back({x, y});
    }
    
    int M; cin >> M;

    for (int i = 0; i < M; i++) {
        int idx, v1, v2; cin >> idx >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    cycle.push_back(0);
    DFS(0, 0, 0, 0);

    if (cycles.size() == 0) {
        cout << -1 << '\n';
        return 0;
    }

    sort(cycles.begin(), cycles.end(), compare());

    for (int c : cycles[0]) cout << c << " ";
    cout << '\n';

    return 0;
}