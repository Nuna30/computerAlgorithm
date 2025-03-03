#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N; cin >> N;
    
    vector<bool> vb (N + 1, false);

    int stdin_count = 0;
    int cardNum;
    while (cin >> cardNum) {
        vb[cardNum] = true;
        stdin_count++;
    }

    int missing_count = N - stdin_count;
    int found_count = 0;
    for (int i = 1; i <= N; i++) {
        if (vb[i] == false) {
            cout << i << endl;
            found_count++;
            if (found_count == missing_count) break;
        }
    }

    return 0;
}