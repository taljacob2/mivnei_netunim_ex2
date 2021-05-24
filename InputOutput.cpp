
#include "InputOutput.h"

/* -- Constructor & Destructor -- */

InputOutput::InputOutput(long int &N, long int &K, std::string &inputFileName,
                         std::string &outputFileName)
    : N(N), K(K), INPUT_FILE_NAME(inputFileName),
      OUTPUT_FILE_NAME(outputFileName) {

    // sets the floating point precision of whole "cout" stream:
    std::cout << std::setprecision(4);
    std::cout << std::fixed;
}

InputOutput::~InputOutput() = default;

/* -- Getters -- */

long int InputOutput::getN() const { return N; }

long int InputOutput::getK() const { return K; }

const std::string &InputOutput::getInputFileName() const {
    return INPUT_FILE_NAME;
}

const std::string &InputOutput::getOutputFileName() const {
    return OUTPUT_FILE_NAME;
}

/* -- Main Methods -- */

void InputOutput::receiveInput(long int &N, long int &K,
                               std::string &inputFileName,
                               std::string &outputFileName) {

    /* Receive N */
    N = getCheckedPositiveLongInt(std::cin);

    /* Receive K */
    K = getCheckedPositiveLongInt(std::cin);

    /* Receive name of InputFile: */
    std::cin >> inputFileName;

    /* Receive name of OutputFile: */
    std::cin >> outputFileName;
}

InputOutput *InputOutput::factoryInputOutput() {

    /* Receive input: */
    long int    N;
    long int    K;
    std::string INPUT_FILE_NAME;
    std::string OUTPUT_FILE_NAME;
    InputOutput::receiveInput(N, K, INPUT_FILE_NAME, OUTPUT_FILE_NAME);

    /* Create InputOutput object */
    return new InputOutput(N, K, INPUT_FILE_NAME, OUTPUT_FILE_NAME);
}

long int *InputOutput::getLongIntArrayFromInputFile() {
    std::ifstream file(INPUT_FILE_NAME);
    if (!file) {

        /* Could not find the file. Throw a message. */
        // std::string message;
        // message.append("Could not find the file: ");
        // message.append(INPUT_FILE_NAME);
        // message.append("\n");

        throw std::runtime_error("wrong input");
    }

    auto *   array = new long int[N];
    long int i     = 0;
    while ((i < N) && (!file.eof())) {
        try {
            array[i] = getCheckedLongInt(file);
        } catch (std::exception &e) {
            delete[] array;
            throw;
        }
        i++;
    }
    if (i < N) {

        /*
         * Means, the file ended earlier than indicated in the provided
         * `N` parameter. This is an error. Throw a message.
         */
        // std::string message;
        // message.append("We have reached the end of the file earlier than "
        //                "expected.\nThe provided `N` parameter is "
        //                "larger than the number of elements received.");
        // message.append("\n");
        // message.append("The `N` provided was: ").append(std::to_string(N));
        // message.append(", and the number of elements received is: ")
        //         .append(std::to_string(i))
        //         .append(".");
        // message.append("\n");

        delete[] array;
        throw std::runtime_error("wrong input");
    }

    file.close();
    return array;
}

/* -- Get Checkers -- */

long int InputOutput::getCheckedLongInt(std::istream &is) noexcept(false) {
    return getChecked<long int>(is, InputOutput::checkLongIntInput, atoi);
}

long int
InputOutput::getCheckedUnsignedLongInt(std::istream &is) noexcept(false) {
    return getChecked<long int>(is, InputOutput::checkUnsignedLongIntInput,
                                atoi);
}

long int
InputOutput::getCheckedPositiveLongInt(std::istream &is) noexcept(false) {
    return getChecked<long int>(is, InputOutput::checkPositiveLongIntInput,
                                atoi);
}

/* -- Checkers -- */

bool InputOutput::checkLongIntInput(std::string &input) {
    bool     returnValue = false;
    long int i           = 0;
    for (; i < (long int) input.length(); i++) {
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

    /* Return `true` only if all iterations have passed successfully. */
    if (i == (long int) input.length()) { returnValue = true; }
    return returnValue;
}

bool InputOutput::checkUnsignedLongIntInput(std::string &input) {
    bool     returnValue = false;
    long int i           = 0;
    for (; i < (long int) input.length(); i++) {
        if (input[i] == '+') {
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

    /* Return `true` only if all iterations have passed successfully. */
    if (i == (long int) input.length()) { returnValue = true; }
    return returnValue;
}

bool InputOutput::checkPositiveLongIntInput(std::string &input) {
    bool     returnValue = false;
    long int i           = 0;
    for (; i < (long int) input.length(); i++) {
        if (input[i] == '+') {
            if (i == 0) {

                /* Okay, only if this is the `first` char in the string. */
                continue;
            } else {

                /* This is not the `first` char in the string. */
                break;
            }
        }
        if (input[i] == '0') {
            if (i == 0) {

                /* Bad, only if this is the `first` char in the string. */
                break;
            } else {

                /* This is not the `first` char in the string. */
                continue;
            }
        } else if (!(('0' <= input[i]) && (input[i] <= '9'))) {

            /* If this is not a number. */
            break;
        }
    }

    /* Return `true` only if all iterations have passed successfully. */
    if (i == (long int) input.length()) { returnValue = true; }
    return returnValue;
}
