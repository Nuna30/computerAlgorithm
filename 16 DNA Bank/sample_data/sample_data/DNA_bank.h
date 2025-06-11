#ifndef DNA_BANK_H
#define DNA_BANK_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

int N ;
long long GLOBAL_SEED ;
vector<string> DNA_SEGMENTS;

char DNA_base(long long seed, int i, int j) {
    if (i < 0 || i >= (int)DNA_SEGMENTS.size()) return '$';
    const string& s = DNA_SEGMENTS[i];
    if (j < 0 || j >= (int)s.size()) return '$';
    return s[j];
}

int get_size() {
    return N;
}

long long get_seed() {
    return GLOBAL_SEED;
}

void set_DNA_bank() {
    ifstream fin("./sample_data/sample_data/03.inp");
    fin >> N;
    fin >> GLOBAL_SEED;

    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    DNA_SEGMENTS.clear();
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            DNA_SEGMENTS.push_back(line);
        }
    }

    fin.close();
}

void get_index(int* idx1, int* idx2) {
    ifstream fin("./sample_data/sample_data/03.inp");

    vector<string> lines;
    string line;
    while (getline(fin, line)) {
        if (!line.empty())
            lines.push_back(line);
    }
    fin.close();

    *idx2 = stoi(lines.back());
    *idx1 = stoi(lines[lines.size() - 2]);
}

void report(int r1, int r2) {
    // ofstream fout("./sample_data/sample_data/02_my.out");
    // fout << r1 << '\n' << r2;
    // fout.close();
}



#endif