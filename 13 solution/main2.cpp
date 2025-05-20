#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;

    vector<int> c(n);
    int min_sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        min_sum += c[i]; 
    }

    int R;
    cin >> R;

    int target = R - min_sum; 
    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = c[i]; j <= target; ++j) {
            dp[j] = (dp[j] + dp[j - c[i]]) % MOD;
        }
    }

    cout << dp[target] << endl;
    return 0;
}
