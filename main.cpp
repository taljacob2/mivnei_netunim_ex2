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
    InputOutput *inputOutput                = nullptr;
    long int *   arrayReceivedFromInputFile = nullptr;
    try {

        /* Receive input, and create an InputOutput object. */
        inputOutput = InputOutput::factoryInputOutput();

        /* Extract array from the `input` file. */
        arrayReceivedFromInputFile =
                inputOutput->getLongIntArrayFromInputFile();
    } catch (std::exception &e) {
        std::cerr << e.what();

        /* Exit program with an error. */
        delete inputOutput;
        return 2;
    }

    /* Sort the `arrayReceivedFromInputFile`. */
    AlgorithmsAndMinHeap::kWayMergeSort(arrayReceivedFromInputFile,
                                        inputOutput->getN(),
                                        inputOutput->getK());

    /* `arrayReceivedFromInputFile` is sorted, print it to `output` file. */
    inputOutput->printArrayToFile(arrayReceivedFromInputFile,
                                  inputOutput->getN(), '\n');

    delete[] arrayReceivedFromInputFile;
    delete inputOutput;
    return 0;
}
