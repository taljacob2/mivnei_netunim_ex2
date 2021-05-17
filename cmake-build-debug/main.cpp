#include <iostream>
#include <string>
#include "InputOutput.h"

/**
 * @mainpage mivnei_netunim targil tichnuti 1
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
int main() {
    InputOutput inputOutput; // local object.
    double *array;
    int size;
    int serialSizeOfTheElementToLookFor;
    double *insertionSortedArray;
    double selectionElementRequested;
    double quintupletElementRequested;

    // get all inputs:
    try {
        array = inputOutput.getAllInputs(size, serialSizeOfTheElementToLookFor);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }

    InputOutput::setSorts(array, size, serialSizeOfTheElementToLookFor,
                          insertionSortedArray, selectionElementRequested,
                          quintupletElementRequested);

    InputOutput::printElements(insertionSortedArray, selectionElementRequested,
                               quintupletElementRequested,
                               serialSizeOfTheElementToLookFor);

    delete[] insertionSortedArray;
    delete[] array;
    return 0;
}
