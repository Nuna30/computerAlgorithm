#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

tuple<int, int, int> build_runaway(const vector<vector<int>>& oc, bool transpose, int N, int M) {
    int max_length = 0;
    int max_x, max_y;
    for (int x = 0; x < N - 1; x++) {
        int y = 0;
        int i1 = 0, i2 = 0;
        int end1 = oc[x].size(), end2 = oc[x + 1].size();
        do {
            // 활주로 길이 계산
            int d1 = oc[x][i1] - y;
            int d2 = oc[x + 1][i2] - y;
            int length = min(d1, d2);
            // 활주로 최대 길이 갱신
            bool c1 = length > max_length;
            bool c2 = !transpose && length == max_length && y <= max_y;
            bool c3 = transpose && length == max_length && y > max_y;
            if (c1 || c2 || c3) {
                max_length = length;
                max_x = x;
                max_y = y;
            }
            // 탐색 지점 가로 이동
            if (d1 < d2) {
                y += (d1 + 1);
                i1++;
            }
            else if (d1 > d2) {
                y += (d2 + 1);
                i2++;
            }
            else {
                y += (d1 + 1);
                i1++; i2++;
            }
        } while (i1 < end1 || i2 < end2);
    }
    // oc2일 시 좌표 전치 
    if (transpose) {int t = max_x; max_x = max_y; max_y = t; N = M;}
    // 좌표 변환 후 반환
    return {max_y + 1, N - max_x, max_length};
}

int main() {
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int N, M; cin >> N >> M;
    // oc : obstacle coordinates
    vector<vector<int>> oc1 (N, vector<int> ());
    vector<vector<int>> oc2 (M, vector<int> ());
    // 장애물 좌표로만 이루어진 2차원 벡터
    // oc1 : 시점 그대로, 가로 탐색에 사용
    // oc2 : 황무지를 transpose, 세로 탐색에 사용
    for (int i = 0; i < N; i++) {
        string row; cin >> row;
        for (int j = 0; j < M; j++) {
            if (row[j] == '1') {
                oc1[i].push_back(j);
                oc2[j].push_back(i);
            }
        }
    }
    // 우측에 가상 장애물 설치 -> 인덱스 경계값 처리 용이
    for (int i = 0; i < N; i++) oc1[i].push_back(M);
    for (int i = 0; i < M; i++) oc2[i].push_back(N);
    // 활주로 계산
    auto [max_x1, max_y1, max_length1] = build_runaway(oc1, false, N, M);
    auto [max_x2, max_y2, max_length2] = build_runaway(oc2, true, M, N);
    // 사전순 더 빠른 거 출력
    bool c1 = max_length1 > max_length2;
    bool c2 = max_length1 == max_length2 && max_x1 < max_x2;
    bool c3 = max_length1 == max_length2 && max_x1 == max_x2 && max_y1 < max_y2;
    if (max_length1 == 0 && max_length2 == 0) printf("%d %d %d\n", 0, 0, 0);
    else if (c1 || c2 || c3) printf("%d %d %d\n", max_x1, max_y1, max_length1);
    else printf("%d %d %d\n", max_x2, max_y2, max_length2);
    return 0;
}