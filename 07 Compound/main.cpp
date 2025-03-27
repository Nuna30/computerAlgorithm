#include <iostream>
#include "battery.h"
#include <utility>

using namespace std;

long long find_maxAmount(char compound, long long lb, long long ub) {
    if (ub == lb) return ub;
    
    long long maxAmount = (lb + ub + 1) / 2;

    int result;
    if (compound == 'x') result = experiment(maxAmount, 1);
    else                 result = experiment(1, maxAmount);

    if (result == 1) return find_maxAmount(compound, maxAmount, ub);
    else             return find_maxAmount(compound, lb, maxAmount - 1);
}

long long find_maxE() {
    long long x = find_maxAmount('x', 1, 100000);
    long long y = find_maxAmount('y', 1, 100000);
    return (x + y) * (x + y);
}

void forSubmission() {
    ready();
    report_maxE(find_maxE());
}

int main() {
    forSubmission();
    return 0;
}