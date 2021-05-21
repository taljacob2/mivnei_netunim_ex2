//
// Created by Tal on 26-Mar-21.
//

#include "InputOutput.h"

InputOutput::InputOutput(int &N, int &K, std::string &inputFileName,
                         std::string &outputFileName)
    : N(N), K(K), INPUT_FILE_NAME(inputFileName),
      OUTPUT_FILE_NAME(outputFileName) {

    // sets the floating point precision of whole "cout" stream:
    std::cout << std::setprecision(4);
    std::cout << std::fixed;
}

InputOutput::~InputOutput() = default;

int InputOutput::getCheckedUnsignedInt(std::istream &is) noexcept(false) {
    return getChecked<int>(is, InputOutput::checkUnsignedIntInput, atoi);
}

int InputOutput::getCheckedInt(std::istream &is) noexcept(false) {
    return getChecked<int>(is, InputOutput::checkIntInput, atoi);
}

bool InputOutput::checkUnsignedIntInput(std::string &input) {
    for (char c : input) {
        if (c > '9' || c < '0') {
            return false; // input is invalid.
        }
    }
    return true; // input is valid.
}

bool InputOutput::checkIntInput(std::string &input) {
    bool returnValue = false;
    int  i           = 0;
    for (; i < input.length(); i++) {
        if ((input[i] == '+') || (input[i] == '-')) {
            if (i == 0) {

                /* Okay, only if this is the `first` char in the string. */
                continue;
            } else {

                /* This is not the `first` char in the string. */
                break;
            }
        } else if (!(('0' <= input[i]) && (input[i] <= '9'))) {

            /* If this is not a number. */
            break;
        }
    }
    if (i == input.length()) { returnValue = true; }
    return returnValue;
}

/* -- Getters & Setters -- */

int InputOutput::getN() const { return N; }

int InputOutput::getK() const { return K; }

const std::string &InputOutput::getInputFileName() const {
    return INPUT_FILE_NAME;
}

const std::string &InputOutput::getOutputFileName() const {
    return OUTPUT_FILE_NAME;
}
