#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N; cin >> N;

    vector<char> buildings (N);
    vector<int> heights (N, 0);
    for (int i = 0; i < N; i++) {
        cin >> buildings[i];
        cin >> heights[i];
    }

    // finding building that cannot view mountain
    int M = 0;
    for (int i = 0; i < N; i++) {
        if (heights[i] > M) {
            M = heights[i];
            cout << buildings[i] << " ";
        }
    }
    cout << endl;

    M = 0;
    stack<char> s;
    for (int i = N - 1; i >= 0; i--) {
        if (heights[i] > M) {
            M = heights[i];
            s.push(buildings[i]);
        }
    }
    
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    return 0;
}