#include "DNA_bank.h"

#include <iostream>
#include <queue>

using namespace std;

int main( ) {
    long long xseed, Nsize;
    char nucleo;
    int  index1, index2, fidx1, fidx2;   
    set_DNA_bank( );   // prepare data set !
    Nsize = get_size( );   // get the number of segments
    xseed = get_seed( );   // get seed number for work
    get_index( &index1, &index2 );

    queue<int> s, a, c, g, t;
    queue<int> idx; for (int i = 0; i < Nsize; i++) idx.push(i);

    for (int j = 100; j >= 0; j--) {
        while (!idx.empty()) {
            int i = idx.front(); idx.pop();
            char DNA = DNA_base(xseed, i, j);
            switch (DNA) {
                case '$' : s.push(i); break;
                case 'a' : a.push(i); break;
                case 'c' : c.push(i); break;
                case 'g' : g.push(i); break;
                case 't' : t.push(i); break;
                default : exit(1);
            }
        }
        while (!s.empty()) idx.push(s.front()), s.pop();
        while (!a.empty()) idx.push(a.front()), a.pop();
        while (!c.empty()) idx.push(c.front()), c.pop();
        while (!g.empty()) idx.push(g.front()), g.pop();
        while (!t.empty()) idx.push(t.front()), t.pop();
    }

    int count = 0;
    while (!idx.empty()) {
        int i = idx.front(); idx.pop();
        if (count == index1) fidx1 = i;
        else if (count == index2) {
            fidx2 = i;
            break;
        }
        count++;
    }

    report( fidx1, fidx2 ) ; // report and quit
}