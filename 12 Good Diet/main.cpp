#include <iostream>
#include <vector>

using namespace std;

// 토큰 초과

int N;
vector<int> comb;
vector<int> costs;
vector<int> min_diets(4, 0);
vector<int> sum_diets(4, 0);
vector<vector<int>> combs;
vector<vector<int>> diets;

void print(const vector<vector<int>>& vvi) {
    cout << '\n';
    for (const vector<int>& vi : vvi) {
        for (int i : vi) cout << i << " ";
        cout << '\n';
    }
    cout << '\n';
}

bool check() {
    for (int i = 0; i < 4; i++) {
        if (sum_diets[i] < min_diets[i]) return false;
    }
    return true;
}

int sum(const vector<int>& vi) {
    int sum = 0;
    for (int i : vi) sum += i;
    return sum;
}

void add(const vector<int>& vi) {
    for (int i = 0; i < 4; i++) sum_diets[i] += vi[i];
}

void subtract(const vector<int>& vi) {
    for (int i = 0; i < 4; i++) sum_diets[i] -= vi[i];
}

void search(int b) {
    if (check()) {
        combs.push_back(comb);
        return;
    }

    for (int i = b + 1; i <= N; i++) {
        comb.push_back(i);
        add(diets[i]);
        search(i);
        comb.pop_back();
        subtract(diets[i]);
    }
}

int main() {
    cin >> N;

    costs.resize(N + 1, 0);
    diets.resize(N + 1, vector<int> (4, 0));

    for (int i = 0; i < 4; i++) cin >> min_diets[i];

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 4; j++) cin >> diets[i][j];
        cin >> costs[i];
    }

    search(0);

    // print(combs);

    for (vector<int>& comb : combs) {
        int sum_diets = 0;
        int sum_costs = 0;
        for (int e : comb) {
            sum_diets += sum(diets[e]);
            sum_costs += costs[e];
        }
        comb.push_back(sum_diets);
        comb.push_back(sum_costs);
    }

    int min_idx = 0;
    int min_diets = combs[0][combs[0].size() - 2];
    int min_cost = combs[0][combs[0].size() - 1];

    for (int i = 1; i < combs.size(); i++) {
        int diets = combs[i][combs[i].size() - 2];
        int cost = combs[i][combs[i].size() - 1];
        // cout << diets << ", " << cost << '\n';
        if (cost < min_cost) {
            min_idx = i;
            min_diets = diets;
            min_cost = cost;
        } else if (cost == min_cost) {
            if (diets > min_diets) {
                min_idx = i;
                min_diets = diets;
                min_cost = cost;
            } 
        }
    }

    // print(combs);

    if (combs.empty()) cout << 0;
    else cout << combs[min_idx][0] << " " << combs[min_idx][1] << " " << combs[min_idx][2];

    return 0;
}