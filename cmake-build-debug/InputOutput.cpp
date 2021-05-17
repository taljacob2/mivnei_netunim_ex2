//
// Created by Tal on 26-Mar-21.
//

#include "InputOutput.h"

InputOutput::InputOutput() {

    // sets the floating point precision of whole "cout" stream:
    std::cout << std::setprecision(4);
    std::cout << std::fixed;

    // if there is already a 'Measure' file, delete it:
    remove(fileName);
}

InputOutput::~InputOutput() = default;

int InputOutput::getSize() noexcept(false) {

    // get the Array size:
    int size;
//    std::cout << "Please input the size of the Array: ";
    std::cin >> _input;
    if (checkLegalUnsignedIntInput(_input)) {

        // if this is a legal input, set as the size of the array:
        size = atoi(_input);
        return size;
    } else {
        my_string msg =
                /*"Found an illegal input: " + _input + "\nExiting program...";*/
                "wrong input";
        throw std::runtime_error(msg.getStr());
    }
}

int InputOutput::getSerialSizeOfTheElementToLookFor(int size) noexcept(false) {

    // get the serialSizeOfTheElementToLookFor:
//    std::cout << "Please input the serialSizeOfTheElementToLookFor in the Array: ";
    int serialSizeOfTheElementToLookFor;
    std::cin >> _input;
    if (checkLegalUnsignedIntInput(_input)) {

        // if this is a legal input, set as the size of the array:
        serialSizeOfTheElementToLookFor = atoi(_input);

        if ((serialSizeOfTheElementToLookFor <= size) &&
            (serialSizeOfTheElementToLookFor >= 1)) {
            return serialSizeOfTheElementToLookFor;
        } else {
            my_string msg =
                    /*"Found an illegal input: out of range: " + _input +
                    "\nExiting program...";*/
                    "wrong input";
            throw std::range_error(msg.getStr());
        }
    } else {
        my_string msg =
                /*"Found an illegal input: " + _input + "\nExiting program...";*/
                "wrong input";
        throw std::runtime_error(msg.getStr());
    }
}

void InputOutput::setArrayContents(double *array, int size) noexcept(false) {

    // get Array content numbers:
//    std::cout << "Please input the number(s) in the Array: ";

    for (int i = 0; i < size; ++i) {

        std::cin >> _input;
        if (checkLegalDoubleInput(_input)) {

            // if this is a legal input, insert it to the array:
            array[i] = atof(_input);
        } else {
            my_string msg =
                    /*"Found an illegal input: " + _input +
                    "\nExiting program...";*/
                    "wrong input";
            throw std::runtime_error(msg.getStr());
        }
    }
}

double *InputOutput::getAllInputs(int &size,
                                  int &serialSizeOfTheElementToLookFor) noexcept(false) {
    double *array = nullptr;
    try {
        // get array 'size' + get 'serialSizeOfTheElementToLookFor':
        size = getSize();
        serialSizeOfTheElementToLookFor =
                getSerialSizeOfTheElementToLookFor(size);

        // create array:
        array = new double[size];
        setArrayContents(array, size);
        return array;
    } catch (std::exception &e) {
        delete[] array;
        throw;
    }
}

bool InputOutput::checkLegalUnsignedIntInput(my_string &input) {
    for (char c : input) {
        if (c > '9' || c < '0') {
            return false; // input is invalid.
        }
    }
    return true; // input is valid.
}

bool InputOutput::checkLegalDoubleInput(my_string &input) {
    unsigned char precision = 0; // current digits after the dot.
    bool dotPassed = false;
    bool signPassed = false;
    for (char c : input) {
        if ((c == '+') || (c == '-')) {
            if (signPassed) {
                return false; // input is invalid. we don't allow more than 1 sign.
            }
            signPassed = true;
            continue;
        }
        if (c == '.') {
            if(dotPassed){
                return false; // input is invalid. we don't allow more than 1 dot.
            }
            dotPassed = true;
            continue;
        }
        if (dotPassed) {
            if (c > '9' || c < '0') {
                return false; // input is invalid. second time pressing '+'/'-' signs.
            }
            if (precision >= 4) {
                return false; // input is invalid. max digits after the dot.
            }
            precision++;
        }
    }
    if (precision == 0) { // at least precision of '1'.
        return false;
    }
    return true;
}
