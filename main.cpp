#include "MinHeap.h"
#include <iostream>


/**
 * @mainpage mivnei_netunim targil tichnuti 2
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
int main() {
    int N = 10;

    auto *arrayToBuildFrom = new Entry<int, std::string>[N];
    for (int i = 0; i < N; i++) {
        arrayToBuildFrom[i] =
                Entry<int, std::string>(N - i, std::to_string(i + 100));
    }

    MinHeap<int, std::string> minHeap;
    minHeap.buildHeap(arrayToBuildFrom, N);
    std::cout << minHeap;

    delete[] arrayToBuildFrom;
    return 0;
}
