#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>

#define MAX_CNT 34

int xlim, ylim, call_cnt = 0;

FILE* in;
FILE* out;

std::string inpFilePath = "C:\\Users\\minhyeon\\Desktop\\univ\\25-1\\컴퓨터알고리즘\\과제\\computerAlgorithm\\07 Compound\\sample_data_2wzMimS";

void ready(int number = 1) {
    char nr[100];  // 충분한 크기의 버퍼 할당
    sprintf(nr, "%.2d", number);  // 두 자릿수로 출력
    std::string path = inpFilePath + "\\" + nr + ".inp";
    in = fopen(path.c_str(), "r");
    fscanf(in, "%d %d", &xlim, &ylim);
}

int experiment(int x, int y) {
    call_cnt += 1;
    // printf("x, y, call_cnt : %d, %d, %d\n", x, y, call_cnt);

    if (call_cnt > MAX_CNT) {
        printf("%d", -999);
        // exit(0);
    }

    if (x > xlim || y > ylim) return -1;
    else return 1;
}

void report_maxE(long long value) {
    printf("your answer : %lld\n", value);
    printf("answer : %lld\n", ((xlim + ylim) * (xlim + ylim)));
    printf("\n");
    if (value == ((xlim + ylim) * (xlim + ylim))) {
        printf("complete!\n");
        // exit(0);
    }
    else printf("fail...\n") ;
}
