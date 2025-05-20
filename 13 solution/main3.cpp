#include <iostream>
#include <vector>

using namespace std;

int count_solutions(int n, const vector<int>& coeffs, int R, int idx, int currentSum) {
    if (idx == n - 1) {
        int remaining = R - currentSum;
        if (remaining > 0 && remaining % coeffs[idx] == 0) return 1;
        else return 0;
    }
    
    int count = 0;
    int max_val = (R - currentSum) / coeffs[idx];
    for (int x = 1; x <= max_val; ++x) {
        int newSum = currentSum + coeffs[idx] * x;
        count += count_solutions(n, coeffs, R, idx + 1, newSum);
    }
    return count;
}

int main() {
    int n;
    cin >> n;

    vector<int> coeffs(n);
    for (int i = 0; i < n; i++) cin >> coeffs[i];

    int R;
    cin >> R;
    
    int result = count_solutions(n, coeffs, R, 0, 0);
    cout << result % 11111 << endl;
    
    return 0;
}