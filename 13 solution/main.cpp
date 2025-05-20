#include <iostream>
#include <vector>

using namespace std;

int mod = 1000000007;

int main() {
 int n;
    cin >> n;

    vector<int> c(n);
    int m = 0;

    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        m += c[i]; 
    }

    int R;
    cin >> R;

    int target = R - m;
    vector<int> dp(target + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = c[i]; j <= target; ++j) {
            dp[j] = (dp[j] + dp[j - c[i]]) % mod;
        }
    }

    cout << dp[target] << endl;
    return 0;
}