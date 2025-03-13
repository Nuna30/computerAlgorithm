#define MAX_CNT 3
#include <stdio.h>

int left[22]  = {0,};
int right[22] = {0,};

char input[23];
int  coins[22];

int balance_call_cnt = 0;

FILE* in;
FILE* out;


void load_coins() {
    in = fopen("your_absolute_path\\test.inp", "r");

    fscanf(in, "%22s", input);

    for (int i = 0; i < 22; i++) {
        coins[i] = input[i] - '0';
    }

    fclose(in);
}


void report_coin(int i) {
    out = fopen("your_absolute_path\\test.out", "w");
    fprintf(out, "%d", i);
    exit(0);
}


int balance(int left[], int right[]) {
    balance_call_cnt += 1;
    if (balance_call_cnt > MAX_CNT) {
        out = fopen("your_absolute_path\\test.out", "w");
        fprintf(out, "Function call limit over");
        exit(0);
    }

    int left_weight = 0, right_weight = 0;

    for (int i=1; i < 22; i++) {
        if (left[i] == 1 && right[i] == 1) {
            return 999;
        }
        if (left[i] != 0 && left[i] != 1) {
            return 999;
        }
        if (right[i] != 0 && right[i] != 1) {
            return 999;
        }
        if (left[i] == 1) {
            left_weight += coins[i];
        }
        if (right[i] == 1) {
            right_weight += coins[i];
        }
    }

    if (left_weight < right_weight) { return 1; }
    else if (left_weight == right_weight) { return 0; }
    else if (left_weight > right_weight) { return -1; }
}