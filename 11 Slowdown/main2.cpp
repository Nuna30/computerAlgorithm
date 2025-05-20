#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct costDescending_pq {
    bool operator() (const tuple<int, int, int>& p1, const tuple<int, int, int>& p2) {
        if (get<0>(p1) == get<0>(p2)) return get<1>(p1) > get<1>(p2);
        return get<0>(p1) < get<0>(p2);
    }
};

int dec(vector<int>& count, int day) {
    for (int i = day; i >= 1; i--) {
        if (count[i] > 0) {count[i]--; return i;}
    }
    return 0;
}

pair<int, int> greedy_sum(const vector<tuple<int, int, int>>& tasks, int T, int K) {
    int sum = 0;
    vector<int> count (T + 1, K);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, costDescending_pq> pq;
    pq.push({0, T, 0});
    for (const tuple<int, int, int>& task : tasks) pq.push(task);

    int pre_cost = 0;
    int pre_decre = 0;
    int min_diff = INT_MAX;
    while (!pq.empty()) {
        auto [cost, day, id] = pq.top(); pq.pop();
        // cout << cost << " " << day << " " << id << '\n'
        int decre = dec(count, day);
        if (decre > 0 && cost > 0) sum += cost, pre_cost = cost, pre_decre = decre;
        else {
            if (pre_decre <= day && pre_cost != cost) min_diff = min(min_diff, pre_cost - cost);
        }
    }
    
    return {sum, sum - min_diff};
}

int main() {
    int N, T, K; cin >> N >> T >> K;

    vector<tuple<int, int, int>> tasks;
    for (int i = 0; i < N; i++) {
        int c, d; cin >> c >> d;
        tasks.push_back({c, d, i}); // {cost, day, id}
    }

    // cout << '\n' << '\n';
    auto [first_max, second_max] = greedy_sum(tasks, T, K);
    cout << first_max << " " << second_max << '\n';

    return 0;
}