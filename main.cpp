#include "InputOutput.h"
#include "MinHeap.h"
#include <iostream>


/**
 * @mainpage mivnei_netunim targil tichnuti 2
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
int main() {

    /* Receive input, and create an InputOutput object */
    InputOutput *inputOutput = InputOutput::factoryInputOutput();

    // /* Create a `Minimum-Heap` from the array. */
    // MinHeap<int, std::string> minHeap(arrayToBuildFrom, N);
    //
    //
    // delete[] arrayToBuildFrom;

    delete inputOutput;
    return 0;
}
