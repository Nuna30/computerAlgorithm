#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int N, min_cost = numeric_limits<int>::max(), max_diet = 0;
vector<int> min_diets(4), costs, sum_diets(4), comb, best_comb;
vector<vector<int>> diets;

bool check() {
    for (int i = 0; i < 4; i++)
        if (sum_diets[i] < min_diets[i]) return false;
    return true;
}

void search(int idx) {
    if (check()) {
        int cost = 0;
        int diet = 0;
        for (int i : comb) {
            cost += costs[i];
            diet += (diets[i][0] + diets[i][1] + diets[i][2] + diets[i][3]);
        }
        if (cost < min_cost || (cost == min_cost && diet > max_diet)) {
            min_cost = cost;
            max_diet = diet;
            best_comb = comb;
        }
        return;
    }
    for (int i = idx + 1; i <= N; i++) {
        comb.push_back(i);
        for (int j = 0; j < 4; j++) sum_diets[j] += diets[i][j];
        search(i);
        for (int j = 0; j < 4; j++) sum_diets[j] -= diets[i][j];
        comb.pop_back();
    }
}

int main() {
    cin >> N;
    costs.resize(N + 1);
    diets.resize(N + 1, vector<int>(4));
    for (int i = 0; i < 4; i++) cin >> min_diets[i];
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 4; j++) cin >> diets[i][j];
        cin >> costs[i];
    }
    search(0);
    if (best_comb.empty()) cout << 0;
    else {
        for (int i : best_comb) cout << i << ' ';
    }
}