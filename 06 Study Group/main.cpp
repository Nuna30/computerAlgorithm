#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;
vector<int> chapterPages;

int distribute_fairly(int lowerBound, int upperBound) {
    int maxPage = (lowerBound + upperBound) / 2;

    int personCount = 1;
    int pages = 0;

    for (int chapterPage : chapterPages) {
        if (pages + chapterPage <= maxPage) {
            pages += chapterPage;
        }
        else {
            pages = chapterPage;
            personCount++;
        }
    }

    if ((upperBound - lowerBound) == 1) {
        if (personCount > K) return upperBound;
        else return lowerBound;
    }

    if (personCount > K) return distribute_fairly(maxPage, upperBound);
    else return distribute_fairly(lowerBound, maxPage);
}

int main() {
    cin >> N >> K;
    chapterPages.resize(N, 0);
    for (int i = 0; i < N; i++) cin >> chapterPages[i];
    
    // 배분된 페이지는 못해도 한 챕터의 페이지 수 보다는 커야함
    int min_page = *max_element(chapterPages.begin(), chapterPages.end());
    int max_page = 20000;
    cout << distribute_fairly(min_page, max_page) << endl;

    return 0;
}