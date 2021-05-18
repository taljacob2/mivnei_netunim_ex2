#include "MinHeap.h"
#include <iostream>


/**
 * @mainpage mivnei_netunim targil tichnuti 2
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
int main() {
    int arrayToBuildFrom[10];
    for (int i = 0; i < 10; i++) { arrayToBuildFrom[i] = 10 - i; }

    MinHeap<int> minHeap(arrayToBuildFrom, 10);
    std::cout << minHeap;


    return 0;
}
