#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int N;
vector<vector<bool>> original;
vector<vector<int>> Zray;

vector<vector<int>> countBCells() {
    vector<vector<int>> BCells (3, vector<int>(2*N - 1, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (original[i][j]) {
                BCells[0][i]++;
                BCells[1][(N - 1) + (i - j)]++;
                BCells[2][i + j]++;
            }
        }
    }

    return BCells;
}

bool check() {
    vector<vector<int>> BCells = countBCells();
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2*N - 1; j++) {
            if (BCells[i][j] != Zray[i + 1][j]) return false;
        }
    }
    return true;
}

void bt(int i, int j, int n) {
    if (n == 0) {
        if (j + 1 == N) {
            if (check()) {
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        if (original[i][j] == true) cout << "B ";
                        else cout << "- ";
                    }
                    cout << '\n';
                }
                exit(0);
            }
            return;
        }
        bt(0, j + 1, Zray[0][j + 1]);
        return;
    }

    for (int I = i; I < N; I++) {
        original[I][j] = true;
        bt(I + 1, j, n - 1);
        original[I][j] = false;
    }
}

void generateZray(int s, int T) {
    for (int i = s; i < s + 2; i++) {
        for (int j = 0; j < T; j++) cin >> Zray[i][j];
    }
}

int main() {
    cin >> N;
    original.resize(N, vector<bool>(N, false));
    Zray.resize(4, vector<int>(2*N - 1, 0));

    generateZray(0, N);
    generateZray(2, 2*N - 1);

    bt(0, 0, Zray[0][0]);
    return 0;
}