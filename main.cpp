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

    int   N                = 1;
    auto *arrayToBuildFrom = new Entry<int, std::string>[N];
    for (int i = 0; i < N; i++) {
        arrayToBuildFrom[i] =
                Entry<int, std::string>(N - i, std::to_string(i + 100));
    }


    /* Create a `Minimum-Heap` from the array. */
    MinHeap<int, std::string> minHeap(arrayToBuildFrom, N);

    /* XXX MY TEST: printing heap */
    std::cout << minHeap;

    /* checking deletion: */
    Entry<int, std::string> *deletedElement = minHeap.deleteMin();
    std::cout << "Removed Element: " << *deletedElement << "\n";


    std::cout << "heap after deletion: \n" << minHeap;

    try {
        Entry<int, std::string> *deletedElement2 = minHeap.deleteMin();
        std::cout << "Removed Element: " << *deletedElement2 << "\n";
    } catch (std::exception &e) { std::cerr << e.what(); }

    std::cout << "heap after deletion2: \n" << minHeap;


    /* XXX : MY TEST: try to insert: */
    auto entryToInsert = Entry(999, std::string("hello"));

    minHeap.insert(&entryToInsert);

    std::cout << "heap after insertion: \n" << minHeap;


    delete[] arrayToBuildFrom;
    return 0;
}
