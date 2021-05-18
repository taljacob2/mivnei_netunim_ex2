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
    int arrayToBuildFrom[N];
    for (int i = 0; i < N; i++) { arrayToBuildFrom[i] = N - i; }

    MinHeap<int> minHeap(arrayToBuildFrom, N);
    std::cout << minHeap;


    return 0;
}
