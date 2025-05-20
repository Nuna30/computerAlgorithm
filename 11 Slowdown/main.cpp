#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;

struct costDescending_pq {
    bool operator() (const tuple<int, int, int>& p1, const tuple<int, int, int>& p2) {
        if (get<0>(p1) == get<0>(p2)) return get<1>(p1) > get<1>(p2);
        return get<0>(p1) < get<0>(p2);
    }
};

bool dec(vector<int>& count, int day) {
    for (int i = day; i >= 1; i--) {
        if (count[i] > 0) {count[i]--; return true;}
    }
    return false;
}

int greedy_sum(const vector<tuple<int, int, int>>& tasks, int T, int K, vector<int>& id_list) {
    int sum = 0;
    vector<int> count (T + 1, K);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, costDescending_pq> pq;
    for (const tuple<int, int, int>& task : tasks) pq.push(task);
    for (int i = 0; i < T * K && !pq.empty();) {
        auto [cost, day, id] = pq.top(); pq.pop();
        // cout << cost << " " << day << " " << id << '\n'
        if (dec(count, day)) sum += cost, i++, id_list.push_back(id);
    }
    
    return sum;
}

int main() {
    int N, T, K; cin >> N >> T >> K;

    vector<tuple<int, int, int>> tasks;
    for (int i = 0; i < N; i++) {
        int c, d; cin >> c >> d;
        tasks.push_back({c, d, i}); // {cost, day, id}
    }

    // cout << '\n' << '\n';
    vector<int> id_list;
    int first_max = greedy_sum(tasks, T, K, id_list);
    int second_max = 0;
    vector<int> vi;
    // for (int id : id_list) {
    //     tuple<int, int, int> temp = tasks[id];
    //     tasks.erase(tasks.begin() + id);
    //     int result = greedy_sum(tasks, T, K, vi);
    //     tasks.insert(tasks.begin() + id, temp);
    //     if (result >= first_max) continue;
    //     second_max = max(second_max, result);
    // }
    for (int i = 0; i < N; i++) {
        tuple<int, int, int> temp = tasks[0];
        tasks.erase(tasks.begin());
        int result = greedy_sum(tasks, T, K, vi);
        tasks.push_back(temp);
        if (result >= first_max) continue;
        second_max = max(second_max, result);
    }


    cout << first_max << " " << second_max << '\n';

    return 0;
}