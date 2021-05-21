#include "AlgorithmsAndMinHeap.h"
#include "InputOutput.h"
#include <iostream>


/**
 * @mainpage mivnei_netunim targil tichnuti 2
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
int main() {

    // FIXME::::::::::::: @link and @endlink -> must change to @ref or
    //  something alike.

    /* Receive input, and create an InputOutput object: */
    InputOutput *inputOutput = InputOutput::factoryInputOutput();

    /* Extract array from the inputFile: */
    int *arrayReceivedFromInputFile = nullptr;
    try {
        arrayReceivedFromInputFile = inputOutput->getIntArrayFromInputFile();
    } catch (std::exception &e) {
        std::cerr << e.what();

        /* Exit program with an error. */
        delete inputOutput;
        return 2;
    }

    /* check: print array received: */
    std::cout << "array received: "
              << "\n";
    for (int i = 0; i < inputOutput->getN(); i++) {
        std::cout << arrayReceivedFromInputFile[i] << " ";
    }
    std::cout << "\n";


    /* Create a `Minimum-Heap` from the array. */
    // MinHeap<int, std::string> minHeap(arrayReceivedFromInputFile, inputOutput->getN());

    AlgorithmsAndMinHeap::kWayMergeSort(&arrayReceivedFromInputFile,
                                        inputOutput->getN(),
                                        inputOutput->getK());

    /* check: print result array: */
    std::cout << "result array: "
              << "\n";
    for (int i = 0; i < inputOutput->getN(); i++) {
        std::cout << arrayReceivedFromInputFile[i] << " ";
    }
    std::cout << "\n";


    delete[] arrayReceivedFromInputFile;
    delete inputOutput;
    return 0;
}
