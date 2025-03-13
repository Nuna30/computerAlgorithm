#define MAX_CNT 3
#include <stdio.h>

int left[22]  = {0,};
int right[22] = {0,};

char input[23];
int  coins[22];

int balance_call_cnt = 0;

FILE* in;
FILE* out;

char pathIn[300];
char pathOut[300];

int load_answer() {
    FILE* answerIn = fopen(pathOut, "r");
    int answer;
    fscanf(answerIn, "%d", &answer);
    fclose(answerIn);
    return answer;
}

void change_path(int i) {
    std::string f = "C:\\Users\\minhyeon\\Desktop\\univ\\25-1\\컴퓨터알고리즘\\과제\\computerAlgorithm\\03 Fake Coin\\sample_data";
    std::string inp = "\\0" + std::to_string(i) + ".inp";
    std::string outp = "\\0" + std::to_string(i) + ".out";
    std::string finp = f + inp;
    strncpy(pathIn, finp.c_str(), 300);
    std::string foutp = f + outp;
    strncpy(pathOut, foutp.c_str(), 300);
}

void load_coins() {
    in = fopen(pathIn, "r");

    fscanf(in, "%22s", input);

    for (int i = 0; i < 22; i++) {
        coins[i] = input[i] - '0';
        printf("%d", coins[i]);
    }
    printf("\n");

    fclose(in);
}


void report_coin(int i) {
    out = fopen(pathIn, "w");
    fprintf(out, "%d", i);
    exit(0);
}


int balance(int left[], int right[]) {
    balance_call_cnt += 1;
    if (balance_call_cnt > MAX_CNT) {
        // out = fopen(path, "w");
        // fprintf(out, "Function call limit over");
        printf("Function call limit over");
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

    if (left_weight > right_weight) { return 1; }
    else if (left_weight == right_weight) { return 0; }
    else if (left_weight < right_weight) { return -1; }
}