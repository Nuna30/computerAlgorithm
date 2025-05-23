#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int N;
vector<vector<bool>> original;
vector<vector<int>> Zray;

vector<vector<int>> countBCells() {
    vector<vector<int>> BCells;

    // check horizontally
    vector<int> counts;
    for (int i = 0; i < N; i++) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (original[i][j] == true) count++;
        }
        counts.push_back(count);
    }
    BCells.push_back(counts);

    // check right down diagonally
    counts.clear();
    for (int j = N - 1; j >= 0; j--) {
        int count = 0;
        for (int i = 0; j + i < N; i++) {
            if (original[i][j + i] == true) count++;
        }
        counts.push_back(count);
    }
    BCells.push_back(counts);

    // check left down diagonally
    counts.clear();
    for (int j = 0; j < N; j++) {
        int count = 0;
        for (int i = 0; j - i >= 0; i++) {
            if (original[i][j - i] == true) count++;
        }
        counts.push_back(count);
    }
    BCells.push_back(counts);

    return BCells;
}

bool check() {
    vector<vector<int>> BCells = countBCells();
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
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

void generateZray(int T) {
    for (int i = 0; i < 2; i++) {
        vector<int> z (T, 0);
        for (int j = 0; j < T; j++) cin >> z[j];
        Zray.push_back(z);
    }
}

int main() {
    cin >> N;
    original.resize(N, vector<bool>(N, false));

    generateZray(N);
    generateZray(2*N - 1);

    bt(0, 0, Zray[0][0]);

    return 0;
}