// #include <iostream>
// #include "myBattery.h"
// #include <utility>

// using namespace std;

// long long find_maxAmount(char compound, long long lb, long long ub) {
//     if (ub == lb) return ub;
    
//     int maxAmount = (lb + ub + 1) / 2;

//     int result;
//     if (compound == 'x') result = experiment(maxAmount, 1);
//     else                 result = experiment(1, maxAmount);

//     if (result == 1) return find_maxAmount(compound, maxAmount, ub);
//     else             return find_maxAmount(compound, lb, maxAmount - 1);
// }

// // long long find_maxE() {
// //     long long x = find_maxAmount('x', 1, 100000);
// //     long long y = find_maxAmount('y', 1, 100000);
// //     printf("my answer : %d, %d\n", x, y);
// //     return (x + y) * (x + y);
// // }

// pair<int, int> find_maxE() {
//     long long x = find_maxAmount('x', 1, 100000);
//     long long y = find_maxAmount('y', 1, 100000);
//     return {x, y};
// }

// void forTest() {
//     for (int i = 1; i <= 6; i++) {
//         ready(i);
//         find_maxE();
//         call_cnt = 0;
//     }
// }

// void debugging() {
//     for (int i = 1; i <= 100000; i++) {
//         for (int j = 1; j <= 100000; j++) {
//             xlim = i;
//             ylim = j;
//             auto [x, y] = find_maxE();
//             if (xlim != x || ylim != y) {
//                 printf("[%d, %d], %d, %d\n", x, y, i, j);
//                 exit(0);
//             }
//             call_cnt = 0;
//         }
//     }
// }

// int main() {
//     // forTest();
//     debugging();
//     return 0;
// }