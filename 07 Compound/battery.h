#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>

#define MAX_CNT 34

int xlim, ylim, call_cnt = 0;

FILE* in;
FILE* out;

void ready() {
    in = fopen("C:\\Users\\minhyeon\\Desktop\\univ\\25-1\\컴퓨터알고리즘\\과제\\computerAlgorithm\\07 Compound\\sample_data_2wzMimS\\06.inp", "r");
    fscanf(in, "%d %d", &xlim, &ylim);
}

int experiment(int x, int y) {
    call_cnt += 1;

    if (call_cnt > MAX_CNT) {
        printf("%d", -999);
        exit(0);
    }

    if (x > xlim || y > ylim) return -1;
    else return 1;
}

void report_maxE(long long value) {
    // out = fopen("your_absolute_path\\test.out", "w");

    // if (value == ((xlim + ylim) * (xlim + ylim))) {
    //     fprintf(out, "%ld", value);
    //     exit(0);
    // }
    // else printf("%d", -999) ;
    std::cout << value << std::endl;
}
