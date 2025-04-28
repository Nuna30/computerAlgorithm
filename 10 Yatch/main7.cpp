#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <tuple>
#include <queue>

#define INF 1000000

using namespace std;

vector<pair<int, int>> points = {{0, 500}};

bool compare1(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

bool compare2(const tuple<int, vector<int>, vector<int>>& p1, const tuple<int, vector<int>, vector<int>>& p2) {
    return get<0>(p1) < get<0>(p2);
}

int d(const pair<int, int>& a, const pair<int, int>& b) {
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    return sqrt(dx*dx + dy*dy);
}

int main() {
    int N; cin >> N;

    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end(), compare1);

    vector<tuple<int, vector<int>, vector<int>>> v1 = {{0, vector<int> (N + 1, 0), {}}};
    vector<tuple<int, vector<int>, vector<int>>> v2;

    for (int i = 1; i <= N; i++) {
        if (v1.size() > 10000) v1.resize(10000);
        for (int j = 0; j < i; j++) {
            for (const auto& pivi : v1) {
                const auto& [dist, inDegree, trace] = pivi;
                if (inDegree[j] > 1) continue;
                tuple<int, vector<int>, vector<int>> p = {dist + d(points[i], points[j]), inDegree, trace};
                auto& [nd, niD, nt] = p;
                niD[i]++;
                niD[j]++;
                nt.push_back(j);
                v2.push_back(p);
                // printf("%5d (", get<0>(v2[v2.size() - 1]));
                // for (int i : get<2>(v2[v2.size() - 1])) printf("%d, ", i);
                // printf(")\n");
            }
        }
        v1 = v2;
        v2.clear();
        sort(v1.begin(), v1.end(), compare2);
    }

    int min_val = INF;
    for (const auto& [dist, inDegree, trace] : v1) {
        int i;
        for (i = 0; i < N; i++) if (inDegree[i] == 1) break;
        int nextDist = dist + d(points[N], points[i]);
        if (nextDist < min_val) min_val = nextDist; 
    }

    cout<< min_val << '\n';
    
    



    return 0;
}