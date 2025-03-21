#include "twofakes.h"
#include <utility>

void putCoins(int scale[], int i, int j) {
    int numberOfCoins = sizeof(coins) / sizeof(coins[0]);
    for (int p = 0; p < numberOfCoins; p++) scale[p] = 0;
    for (int p = i; p <= j; p++) scale[p] = 1;
}

int test(int li, int lj, int ri, int rj) {
    putCoins(left, li, lj);
    putCoins(right, ri, rj);
    return balance(left, right);
}

int search1(int i, int j) {
    int size = j - i + 1;
    int splitSize = size / 3;

    if (size == 1) return i;
    else if (size == 2) return ((test(i, i, j, j) == -1) ? i : j);

    int L1 = i,      L2 = L1 + splitSize - 1;
    int R1 = L2 + 1, R2 = R1 + splitSize - 1;
    int O1 = R2 + 1, O2 = j; 

    int result = test(L1, L2, R1, R2);
    if (result == -1) return search1(L1, L2);
    else if (result == 1) return search1(R1, R2);
    else return search1(O1, O2);
}

std::pair<int, int> search2(int i, int j) {
    int size = j - i + 1;
    int splitSize = size / 3;

    int L1 = i,      L2 = L1 + splitSize - 1;
    int R1 = L2 + 1, R2 = R1 + splitSize - 1;
    int O1 = R2 + 1, O2 = j; 

    int result1 = test(L1, L2, R1, R2);
    int result2 = test(R1, R2, O1, O2);
    if (result1 == 0) {
        if (result2 == -1) return {search1(L1, L2), search1(R1, R2)};
        else return search2(O1, O2);
    } else if (result1 == -1) {
        if (result2 == 1) return {search1(L1, L2), search1(O1, O2)};
        else return search2(L1, L2);
    } else {
        if (result2 == 0) return {search1(R1, R2), search1(O1, O2)};
        else return search2(R1, R2);
    }
}

int main() {
    load_coins();
    auto [idx1, idx2] = search2(1, 10);
    two_fakes(idx1, idx2);
    return 0;
}