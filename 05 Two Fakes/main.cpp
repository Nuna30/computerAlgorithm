#include "twofakes.h"
// #include <utility>

// void putCoins(int scale[], int i, int j) {
//     // scale : left[] / right[]
//     int numberOfCoins = sizeof(coins) / sizeof(coins[0]);
//     for (int p = 0; p < numberOfCoins; p++) scale[p] = 0;
//     for (int p = i; p <= j; p++) scale[p] = 1;
// }

// int test(int li, int lj, int ri, int rj) {
//     putCoins(left, li, lj);
//     putCoins(right, ri, rj);
//     return balance(left, right);
// }

// int search1of3(int i, int j) {
//     int result = test(i, i, i + 1, i + 1);
//     switch (result) {
//         case -1 : return i;
//         case 1 : return i + 1;
//         case 0 : return i + 2;
//     }
// }

// int search1of4(int i, int j) {
//     int result = test(i, i, i + 1, i + 1);
//     if (result == 0) return ((test(j - 1, j - 1, j, j) == -1) ? j - 1 : j);
//     else return ((result == -1) ? i : i + 1);
// }

// std::pair<int, int> search2of3(int i, int j) {
//     int result = test(i, i, i + 1, i + 1);
//     if (result == 0) return {i, i + 1};
//     else if (result == -1) return {i, i + 2};
//     else return {i + 1, j};
// }

// std::pair<int, int> search2of4(int i, int j) {
//     int result1 = test(i, i, i + 1, i + 1);
//     int result2 = test(i + 1, i + 1, j - 1, j - 1);
//     if (result1 == 0) {
//         if (result2 == -1) return {i, i + 1};
//         else return {j - 1, j};
//     } else if (result1 == -1) {
//         if (result2 == 1) return {i, j - 1};
//         else return {i, j};
//     } else {
//         if (result2 == 0) return {i + 1, j - 1};
//         else return {i + 1, j};
//     }
// }

// std::pair<int, int> search() {
//     int result1 = test(1, 3, 4, 6);
//     int result2 = test(4, 6, 7, 10);
//     if (result1 == 0) {
//         if (result2 == -1) return {search1of3(1, 3), search1of3(4, 6)};
//         else return search2of4(7, 10);
//     } else if (result1 == -1) {
//         if (result2 == 1) return {search1of3(1, 3), search1of4(7, 10)};
//         else return search2of3(1, 3);
//     } else {
//         if (result2 == 0) return {search1of3(4, 6), search1of4(7, 10)};
//         else return search2of3(4, 6);
//     }
// }

int main() {
    // concatenate();
    // load_coins();
    // // auto [idx1, idx2] = search();
    // int idx1 = 1;
    // int idx2 = 2;
    // two_fakes(idx1, idx2);
    return 0;
}