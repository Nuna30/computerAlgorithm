#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;


bool test(string input, string output) {
    int N, M;
    vector<vector<int>> dome;
    vector<vector<vector<int>>> obstacle;
    vector<vector<int>> dp1;
    vector<vector<int>> dp2;
    ifstream file(input);
    file >> N;
    file >> M;

    dome.resize(N, vector<int> (M, 0));
    obstacle.resize(N, vector<vector<int>> (M, {1, 1, 1, 1}));
    dp1.resize(N, vector<int> (M, 1));
    dp2.resize(N, vector<int> (M, 1));

    for (int i = 0; i < N; i++) {
        string str; file >> str;
        for (int j = 0; j < M; j++) {
            dome[i][j] = str[j] - '0';
            if (dome[i][j] == 1) {
                obstacle[i][j] = {0, 0, 0, 0};
                dp1[i][j] = 0;
                dp2[i][j] = 0;
            }
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


    int max_range = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            set<int> UL_set;
            set<int> NUNL_set;

            int A = dp1[i - 1][j - 1] + 1;
            int B = dp2[i - 1][j - 1] + 1; // B는 최대 search range
            int U = min(B, obstacle[i][j][0]);
            int L = min(B, obstacle[i][j][1]);
            int NU = INT_MAX; if (i - U - 1 >= 0) NU = min(B, U + 1 + obstacle[i - U - 1][j][0]);
            int NL = INT_MAX; if (j - L - 1 >= 0) NL = min(B, L + 1 + obstacle[i][j - L - 1][1]);

            vector<int> vi = {A, B, U, L, NU, NL};
            if (dome[i][j] == 1) vi = {0, A, B, NU, NL};
            sort(vi.begin(), vi.end());

            dp1[i][j] = vi[0];
            dp2[i][j] = vi[1];

            if (dp2[i][j] > max_range) max_range = dp2[i][j];
        }
    }

    for (int j = 0; j < M; j++) {
        for (int i = N - 1; i >= 0; i--) {
            if (dp2[i][j] == max_range) {
                int x = j - max_range + 2;
                int y = N - i;
                ifstream outputfile (output);
                int ox, oy, answer; outputfile >> ox >> oy >> answer;
                printf("%d %d %d ", x, y, max_range);
                printf("%d %d %d\n", ox, oy, answer);
                if (x == ox && y == oy && max_range == answer) return true;
                else return false;
            }
        }
    }
}

int main() {
    for (int i = 1; i <= 7; i++) {
        string folder = "sample_data/";
        string input = folder + "0" + to_string(i) + ".inp";
        string output = folder + "0" + to_string(i) + ".out";
        printf("test %d : ", i);
        if (test(input, output)) printf("correct\n");
        else printf("wrong\n");
        printf("\n");
    }

    return 0;
}