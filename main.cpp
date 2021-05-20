#include "MinHeap.h"
#include <iostream>


/**
 * @mainpage mivnei_netunim targil tichnuti 2
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
int main() {

    /* XXX MY TEST: Generating an Input Array */

    int   N                = 10;
    auto *arrayToBuildFrom = new Entry<int, std::string>[N];
    for (int i = 0; i < N; i++) {
        arrayToBuildFrom[i] =
                Entry<int, std::string>(N - i, std::to_string(i + 100));
    }


    /* Create a `Minimum-Heap` from the array. */
    MinHeap<int, std::string> minHeap(arrayToBuildFrom, N);

    /* XXX MY TEST: printing heap */
    std::cout << minHeap;


    delete[] arrayToBuildFrom;
    return 0;
}
