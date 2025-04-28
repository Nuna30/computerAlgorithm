#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<vector<int>> dp1, dp2, dome;
vector<vector<vector<int>>> obstacle;

int main() {
    int N, M; cin >> N >> M;
    dp1 = dp2 = dome = vector<vector<int>>(N, vector<int>(M, 1));
    obstacle = vector<vector<vector<int>>>(N, vector<vector<int>>(M, {1, 1, 1, 1}));

    for (int i = 0; i < N; i++) {
        string str; cin >> str;
        for (int j = 0; j < M; j++) {
            dome[i][j] = str[j] - '0';
            if (dome[i][j]) {
                obstacle[i][j] = {0, 0, 0, 0};
                dp1[i][j] = dp2[i][j] = 0;
            }
        }
    }

    int max_range = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {

            if (obstacle[i][j][0]) obstacle[i][j][0] = obstacle[i - 1][j][0] + 1;
            if (obstacle[i][j][1]) obstacle[i][j][1] = obstacle[i][j - 1][1] + 1;

            int A = dp1[i - 1][j - 1] + 1;
            int B = dp2[i - 1][j - 1] + 1;
            int U = min(B, obstacle[i][j][0]);
            int L = min(B, obstacle[i][j][1]);
            int NU = INT_MAX; if (i - U - 1 >= 0) NU = min(B, U + 1 + obstacle[i - U - 1][j][0]);
            int NL = INT_MAX; if (j - L - 1 >= 0) NL = min(B, L + 1 + obstacle[i][j - L - 1][1]);

            vector<int> vi = {A, B, U, L, NU, NL};
            if (dome[i][j]) vi = {0, A, B, NU, NL};
            sort(vi.begin(), vi.end());

            dp1[i][j] = vi[0];
            dp2[i][j] = vi[1];
            if (dp2[i][j] > max_range) max_range = dp2[i][j];
        }
    }

    for (int j = 0; j < M; j++) {
        for (int i = N - 1; i >= 0; i--) {
            if (dp2[i][j + max_range - 1] == max_range) {
                printf("%d %d\n%d", j + 1, N - i, max_range);
                return 0;
            }
        }
    }

    return 0;
}
