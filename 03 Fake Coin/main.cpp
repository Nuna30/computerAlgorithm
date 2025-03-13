#include <iostream>
#include <cstring>
#include <utility>
#include "fakecoin.h"

void putCoin(int arr[], int s, int e) {
    for (int i = 1; i < s; i++) arr[i] = 0;
    for (int i = s; i < e; i++) arr[i] = 1;
    for (int i = e; i < 22; i++) arr[i] = 0;
}

// 첫 split 시 우선 가짜 코인의 범위를 찾은 후, 범위를 해당 범위보다 큰 3^n으로 확장
// ex) 21이 7로 쪼개진 후 9로 확장
// ex) 24이 8로 쪼개진 후 9로 확장
// ex) 35이 11로 쪼개진 후 27로 확장
std::pair<int, int> preProcess(int s, int e) {
    int totalLength = e - s;
    int splitLength = totalLength / 3;

    int m1 = s + splitLength;
    int m2 = m1 + splitLength;

    putCoin(left, s, m1);
    putCoin(right, m1, m2);

    int i, j; // s ~ e를 3^n에 맞게 확장시킨 i ~ j
    int b = balance(left, right);
    if (b == -1) {i = s; j = m1;}
    else if (b == 1) {i = m1; j = m2;}
    else {i = m2; j = e;}

    if (splitLength % 3 > 0) {
        int N = 3;
        while (N < splitLength) N *= 3;
        if (i + N <= e) j = i + N; // j에서 확장
        else i -= N - (e - i); // 범위 초과 시 e까지 확장 후 i에서 왼쪽으로 확장
    }

    return {i, j};
}

// 항상 3으로 떨어지게 전처리 된 [s, e)를 탐색
int ternarySearch(int s, int e) {
    int splitLength = (e - s) / 3; // 항상 3으로 떨어지게 
    int m1 = s + splitLength;
    int m2 = m1 + splitLength;
    putCoin(left, s, m1);
    putCoin(right, m1, m2);
    int b = balance(left, right);
    if (splitLength == 1) {
        if (b == -1) return s;
        else if (b == 1) return m1;
        else return m2;
    }
    else if (b == -1) return ternarySearch(s, m1);
    else if (b == 1) return ternarySearch(m1, m2);
    else return ternarySearch(m2, e);
}

int main() {
    load_coins();
    auto [s, e] = preProcess(1, 22);
    int fake_coin = ternarySearch(s, e);
    report_coin(fake_coin);
    return 0;
}