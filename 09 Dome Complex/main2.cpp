#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> dome;
vector<vector<vector<int>>> obstacle;
vector<vector<int>> dp1;
vector<vector<int>> dp2;

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
    dp2.resize(N, vector<int> (M, 1));

    for (int i = 0; i < N; i++) {
        string str; cin >> str;
        for (int j = 0; j < M; j++) {
            dome[i][j] = str[j] - '0';
            if (dome[i][j] == 1) obstacle[i][j] = {0, 0, 0, 0};
        }
    }

    int di[] = {-1, 0};
    int dj[] = {0, -1};

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            for (int k = 0; k < 2; k++) {
                int ni = i + di[k];
                int nj = j + dj[k];
                if (obstacle[i][j][k] != 0) obstacle[i][j][k] = obstacle[ni][nj][k] + 1;
            }
        }
    }

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            int A = dp1[i - 1][j - 1] + 1;
            int B = dp2[i - 1][j - 1] + 1;
            int U = min(B, obstacle[i][j][0]);
            int L = min(B, obstacle[i][j][1]);
            dp1[i][j] = min({A, U, L});

            int NU = INT_MAX; if (i - U - 1 >= 0) NU = min(B, obstacle[i - U - 1][j][0]);
            int NL = INT_MAX; if (j - L - 1 >= 0) NL = min(B, obstacle[i][j - L - 1][1]);
            vector<int> vi = {A, U, L, NU, NL};
            if (dome[i][j] == 1) vi = {0, A, obstacle[i - 1][j][0], obstacle[i][j - 1][1]};
            sort(vi.begin(), vi.end());
            dp2[i][j] = vi[1];
        }
    }

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < M; j++) {
    //         if (dome[i][j] == 1) printf(" [%d]", dp1[i][j]);
    //         else printf("%3d ", dp1[i][j]);
    //     }
    //     printf("\n\n");
    // }
    // printf("\n");

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