#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <limits>

using namespace std;

int N, M;
vector<vector<int>> dome;
vector<vector<vector<int>>> obstacle;
vector<vector<int>> dp1;
vector<vector<pair<int, int>>> dp2;

// void print_obstacle () {
//     for (int k = 0; k < 4; k++) {
//         for (int i = 0; i < N; i++) {
//             for (int j = 0; j < M; j++) {
//                 printf("%2d ", obstacle[i][j][k]);
//             }
//             printf("\n");
//         }
//         printf("\n");
//     }
// }

int main() {
    cin >> N >> M;
    dome.resize(N, vector<int> (M, 0));
    obstacle.resize(N, vector<vector<int>> (M, {1, 1, 1, 1}));
    dp1.resize(N, vector<int> (M, 1));
    dp2.resize(N, vector<pair<int, int>> (M, {1, 0}));

    for (int i = 0; i < N; i++) {
        string str; cin >> str;
        for (int j = 0; j < M; j++) {
            dome[i][j] = str[j] - '0';
            if (dome[i][j] == 1) obstacle[i][j] = {0, 0, 0, 0};
        }
    }

    int di[] = {-1, 0, 1, 0};
    int dj[] = {0, -1, 0, 1};

    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < M - 1; j++) {
            for (int k = 0; k < 2; k++) {
                int ni = i + di[k];
                int nj = j + dj[k];
                if (obstacle[i][j][k] != 0) obstacle[i][j][k] = obstacle[ni][nj][k] + 1;
            }
        }
    }

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            // int obsCount = 0;
            // if (obstacle[i][j][0] <= dp2[i - 1][j - 1].first) obsCount++;
            // if (obstacle[i][j][1] <= dp2[i - 1][j - 1].first) obsCount++;
            // if (dome[i][j] == 1) obsCount--;
            int minObs = min(obstacle[i][j][0], obstacle[i][j][1]);
            dp1[i][j] = min(dp1[i - 1][j - 1] + 1, minObs);
            
            if (minObs <= dp2[i - 1][j - 1].first) {
                if (dp2[i - 1][j - 1].second == 0) {
                    dp2[i][j].second = 1;
                    dp2[i][j].first  = dp2[i - 1][j - 1].first + 1;
                }
                else {
                    dp2[i][j].second = dp2[i - 1][j - 1].second;
                    if (dome[i][j] == 1) dp2[i][j].first = dp1[i - 1][j - 1] + 1;
                    else dp2[i][j].first = min(dp1[i - 1][j - 1], dp1[i][j]) + 1;
                    // if (obsCount == 2) dp2[i][j].first = dp1[i][j] + 1;
                    // else dp2[i][j].first  = dp1[i - 1][j - 1] + 1;
                }
            }
            else dp2[i][j] = {dp2[i - 1][j - 1].first + 1, dp2[i - 1][j - 1].second};
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (dome[i][j] == 1) printf(" [%d]", dp1[i][j]);
            else printf("%3d ", dp1[i][j]);
        }
        printf("\n\n");
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (dome[i][j] == 1) printf(" [%d]", dp2[i][j]);
            else printf("%3d ", dp2[i][j]);
        }
        printf("\n\n");
    }
    printf("\n");

    return 0;
}