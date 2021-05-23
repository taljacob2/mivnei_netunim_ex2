
#include "InputOutput.h"

/* -- Constructor & Destructor -- */

InputOutput::InputOutput(int &N, int &K, std::string &inputFileName,
                         std::string &outputFileName)
    : N(N), K(K), INPUT_FILE_NAME(inputFileName),
      OUTPUT_FILE_NAME(outputFileName) {

    // sets the floating point precision of whole "cout" stream:
    std::cout << std::setprecision(4);
    std::cout << std::fixed;
}

InputOutput::~InputOutput() = default;

/* -- Getters -- */

int InputOutput::getN() const { return N; }

int InputOutput::getK() const { return K; }

const std::string &InputOutput::getInputFileName() const {
    return INPUT_FILE_NAME;
}

const std::string &InputOutput::getOutputFileName() const {
    return OUTPUT_FILE_NAME;
}

/* -- Main Methods -- */

void InputOutput::receiveInput(int &N, int &K, std::string &inputFileName,
                               std::string &outputFileName) {

    /* Receive N */
    N = getCheckedPositiveInt(std::cin);

    /* Receive K */
    K = getCheckedPositiveInt(std::cin);

    /* Receive name of InputFile: */
    std::cin >> inputFileName; // TODO: need to check this somehow?

    /* Receive name of OutputFile: */
    std::cin >> outputFileName; // TODO: need to check this somehow?
}

InputOutput *InputOutput::factoryInputOutput() {

    /* Receive input: */
    int         N;
    int         K;
    std::string INPUT_FILE_NAME;
    std::string OUTPUT_FILE_NAME;
    InputOutput::receiveInput(N, K, INPUT_FILE_NAME, OUTPUT_FILE_NAME);

    /* Create InputOutput object */
    return new InputOutput(N, K, INPUT_FILE_NAME, OUTPUT_FILE_NAME);
}

int *InputOutput::getIntArrayFromInputFile() {
    std::ifstream file(INPUT_FILE_NAME);
    if (!file) {

        /* Could not find the file. Throw a message. */
        std::string message;
        message.append("Could not find the file: ");
        message.append(INPUT_FILE_NAME);
        message.append("\n");

        // TODO: change to `wrong input`
        throw std::runtime_error(message);
    }

    auto *array = new int[N];
    int   i     = 0;
    while ((i < N) && (!file.eof())) {
        try {
            array[i] = getCheckedInt(file);
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
        std::string message;
        message.append("We have reached the end of the file earlier than "
                       "expected.\nThe provided `N` parameter is "
                       "larger than the number of elements received.");
        message.append("\n");
        message.append("The `N` provided was: ").append(std::to_string(N));
        message.append(", and the number of elements received is: ")
                .append(std::to_string(i))
                .append(".");
        message.append("\n");

        // TODO: change to `wrong input`
        delete[] array;
        throw std::runtime_error(message);
    }

    file.close();
    return array;
}

/* -- Get Checkers -- */

int InputOutput::getCheckedInt(std::istream &is) noexcept(false) {
    return getChecked<int>(is, InputOutput::checkIntInput, atoi);
}

int InputOutput::getCheckedUnsignedInt(std::istream &is) noexcept(false) {
    return getChecked<int>(is, InputOutput::checkUnsignedIntInput, atoi);
}

int InputOutput::getCheckedPositiveInt(std::istream &is) noexcept(false) {
    return getChecked<int>(is, InputOutput::checkPositiveIntInput, atoi);
}

/* -- Checkers -- */

bool InputOutput::checkIntInput(std::string &input) {
    bool returnValue = false;
    int  i           = 0;
    for (; i < (int) input.length(); i++) {
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
    if (i == (int) input.length()) { returnValue = true; }
    return returnValue;
}

bool InputOutput::checkUnsignedIntInput(std::string &input) {
    bool returnValue = false;
    int  i           = 0;
    for (; i < (int) input.length(); i++) {
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
    if (i == (int) input.length()) { returnValue = true; }
    return returnValue;
}

bool InputOutput::checkPositiveIntInput(std::string &input) {
    bool returnValue = false;
    int  i           = 0;
    for (; i < (int) input.length(); i++) {
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
    if (i == (int) input.length()) { returnValue = true; }
    return returnValue;
}
