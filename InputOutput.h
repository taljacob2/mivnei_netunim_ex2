
#ifndef MIVNEI_NETUNIM_EX2_INPUTOUTPUT_H
#define MIVNEI_NETUNIM_EX2_INPUTOUTPUT_H

#include "my_algorithms.h"
#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>

/**
 * @brief this class bundles together all the input / output
 *        methods of the program.
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
class InputOutput {
  private:
    /// The number of elements provided.
    const int N;

    /// The division parameter.
    const int K;

    /// The name of the `input` file.
    const std::string INPUT_FILE_NAME;

    /// The name of the `output` file.
    const std::string OUTPUT_FILE_NAME;

    /* -- Constructor & Destructor -- */
  public:
    InputOutput(int &N, int &K, std::string &inputFileName,
                std::string &outputFileName);

    ~InputOutput();

    /* -- Getters -- */
  public:
    int                getN() const;
    int                getK() const;
    const std::string &getInputFileName() const;
    const std::string &getOutputFileName() const;

    /* -- Main Methods -- */
  public:
    static void receiveInput(int &N, int &K, std::string &inputFileName,
                             std::string &outputFileName);

    /**
     * @brief This method serves as a **Factory** method.
     *
     * Receives input:
     *      @li (int) N - the number of elements provided.
     *      @li (int) K - the division parameter.
     *      @li (std::string) INPUT_FILE_NAME - the name of the `inputFile`.
     *      @li (std::string) OUTPUT_FILE_NAME - the name of the `outputFile`.
     *
     * Construction:
     *      @li Constructs a `new` *InputOutput* object from the given input, and
     *      returns it.
     * @return Constructs a `new` *InputOutput* object from the given input,
     * and returns it.
     * @see InputOutput(int&, int&, std::string&, std::string&)
     */
    static InputOutput *factoryInputOutput();

    /**
     * @brief This method gets the `array` specified in the *INPUT_FILE*
     *        provided by the *INPUT_FILE_NAME*.
     *
     * @return the *int* array specified in the *INPUT_FILE* .
     * @throws std::runtime_error @li in case the *file* specified by the
     *                            name: `INPUT_FILE_NAME` could not be found.
     *                            @li in case the `N` provided in the *file*
     *                            is larger than the actual number of elements
     *                            provided in the *file*.
     */
    int *getIntArrayFromInputFile();

    /* -- Print Methods -- */

    /**
     * @brief Prints an @p array to an `output-stream`.
     *
     * @tparam T the `type` of elements in the @p array given.
     * @param os the `output-stream` to print the array to.
     * @param array the array to be printed.
     * @param size the size of the @p array to be printed.
     */
    template<typename T>
    static void printArray(std::ostream &os, T *array, int size) {
        for (int i = 0; i < size; i++) { os << array[i] << " "; }
        os << "\n";
    }

    /**
     * @brief Prints an @p array to an `output-stream`, such that after each
     *        element printed, we print a @p delimiter `char`.
     *
     * @note the @p delimiter `char` is *not* printed after the `last` element.
     * @tparam T the `type` of elements in the @p array given.
     * @param os the `output-stream` to print the array to.
     * @param array the array to be printed.
     * @param size the size of the @p array to be printed.
     * @param delimiter the `char` to be printed in between the printed
     *                  elements. Means, this method prints this `char` after
     *                  each element but the `last` element.
     */
    template<typename T>
    static void printArray(std::ostream &os, T *array, int size,
                           char delimiter) {
        int i = 0;
        for (; i < size - 1; i++) { os << array[i] << delimiter; }
        os << array[i];
    }

    /**
     * @brief Prints an @p array to an `output` file.
     *
     * @tparam T the `type` of elements in the @p array given.
     * @param array the array to be printed.
     * @param size the size of the @p array to be printed.
     * @throws std::runtime_error in case the *file* specified by the
     *                            name: @p outputFileName could not be opened.
     */
    template<typename T>
    static void printArrayToFile(std::string &outputFileName, T *array,
                                 int size) {
        std::ofstream file(outputFileName);
        if (!file) {

            /* Could not open the file. Throw a message. */
            // std::string message;
            // message.append("Could not open the file: ");
            // message.append(outputFileName);
            // message.append("\n");

            throw std::runtime_error("wrong input");
        }

        for (int i = 0; i < size; i++) { file << array[i] << " "; }
        file << "\n";
        file.close();
    }

    /**
     * @brief Prints an @p array to an `output` file, such that after each
     *        element printed, we print a @p delimiter `char`.
     *
     * @note the @p delimiter `char` is *not* printed after the `last` element.
     * @tparam T the `type` of elements in the @p array given.
     * @param outputFileName the name of the `output` file to print the array
     *                       to.
     * @param array the array to be printed.
     * @param size the size of the @p array to be printed.
     * @param delimiter the `char` to be printed in between the printed
     *                  elements. Means, this method prints this `char` after
     *                  each element but the `last` element.
     * @throws std::runtime_error in case the *file* specified by the
     *                            name: @p outputFileName could not be opened.
     */
    template<typename T>
    static void printArrayToFile(std::string &outputFileName, T *array,
                                 int size, char delimiter) {
        std::ofstream file(outputFileName);
        if (!file) {

            /* Could not open the file. Throw a message. */
            // std::string message;
            // message.append("Could not open the file: ");
            // message.append(outputFileName);
            // message.append("\n");

            throw std::runtime_error("wrong input");
        }
        int i = 0;
        for (; i < size - 1; i++) { file << array[i] << delimiter; }
        file << array[i];
        file.close();
    }

    /**
     * @brief Prints an @p array to the file named *OUTPUT_FILE_NAME*.
     *
     * @tparam T the `type` of elements in the @p array given.
     * @param array the array to be printed.
     * @param size the size of the @p array to be printed.
     * @throws std::runtime_error in case the *file* specified by the
     *                            name: `OUTPUT_FILE_NAME` could not be opened.
     */
    template<typename T> void printArrayToFile(T *array, int size) {
        std::ofstream file(OUTPUT_FILE_NAME);
        if (!file) {

            /* Could not open the file. Throw a message. */
            // std::string message;
            // message.append("Could not open the file: ");
            // message.append(OUTPUT_FILE_NAME);
            // message.append("\n");

            throw std::runtime_error("wrong input");
        }

        for (int i = 0; i < size; i++) { file << array[i] << " "; }
        file << "\n";
        file.close();
    }

    /**
     * @brief Prints an @p array to the file named *OUTPUT_FILE_NAME*, such
     *        that after each element printed, we print a @p delimiter `char`.
     *
     * @note the @p delimiter `char` is *not* printed after the `last` element.
     * @tparam T the `type` of elements in the @p array given.
     * @param array the array to be printed.
     * @param size the size of the @p array to be printed.
     * @param delimiter the `char` to be printed in between the printed
     *                  elements. Means, this method prints this `char` after
     *                  each element but the `last` element.
     * @throws std::runtime_error in case the *file* specified by the
     *                            name: `OUTPUT_FILE_NAME` could not be opened.
     */
    template<typename T>
    void printArrayToFile(T *array, int size, char delimiter) {
        std::ofstream file(OUTPUT_FILE_NAME);
        if (!file) {

            /* Could not open the file. Throw a message. */
            // std::string message;
            // message.append("Could not open the file: ");
            // message.append(OUTPUT_FILE_NAME);
            // message.append("\n");

            throw std::runtime_error("wrong input");
        }
        int i = 0;
        for (; i < size - 1; i++) { file << array[i] << delimiter; }
        file << array[i];
        file.close();
    }

    /* -- Get Checkers -- */
  public:
    /**
     * @brief This method receives an `input` from an `input-stream` and checks
     *        whether it is a legal **Int**.
     *
     * @li In case the `input` gotten is `legal / valid`, return in.
     * @li In case the `input` gotten is `illegal / invalid`, throw an
     * exception.
     * @param is the `input-stream` to get the `input` from.
     * @return the `input` gotten from the `input-stream` @p is, after
     *         passing the checking validation.
     * @throws std::runtime_error if the `input` is in an `illegal` format.
     * @see checkIntInput(std::string &)
     * @see getChecked
     */
    static int getCheckedInt(std::istream &is);

    /**
     * @brief This method receives an `input` from an `input-stream` and checks
     *        whether it is a legal **UnsignedInt**.
     *
     * @li In case the `input` gotten is `legal / valid`, return in.
     * @li In case the `input` gotten is `illegal / invalid`, throw an
     * exception.
     * @param is the `input-stream` to get the `input` from.
     * @return the `input` gotten from the `input-stream` @p is, after
     *         passing the checking validation.
     * @throws std::runtime_error if the `input` is in an `illegal` format.
     * @see checkUnsignedIntInput(std::string &)
     * @see getChecked
     */
    static int getCheckedUnsignedInt(std::istream &is);

    /**
     * @brief This method receives an `input` from an `input-stream` and checks
     *        whether it is a legal **PositiveInt**.
     *
     * @li In case the `input` gotten is `legal / valid`, return in.
     * @li In case the `input` gotten is `illegal / invalid`, throw an
     * exception.
     * @param is the `input-stream` to get the `input` from.
     * @return the `input` gotten from the `input-stream` @p is, after
     *         passing the checking validation.
     * @throws std::runtime_error if the `input` is in an `illegal` format.
     * @see checkPositiveIntInput(std::string &)
     * @see getChecked
     */
    static int getCheckedPositiveInt(std::istream &is);

  private:
    /**
     * @brief This method gets an input from an `input-stream` @p is,
     *        and after that, *checks* whether the input gotten is legal by
     *        checking it with a specific function: @p checkingFunction.
     *        In case the input was found as legal, then we manipulate the
     *        checked input with the @p returnFunction, and its `return`
     *        value is set to be this method's return value.
     *
     * @tparam T is the type of the value to get.
     * @param is is the `input-stream` to get the value from.
     * @param checkingFunction is the checking function that checks that the
     *                         input gotten is legal.
     * @param returnFunction is the function that is being invoked finally
     *                       in its method. Its `return` value is the final
     *                       return value of this method.
     * @return the checked `input` gotten.
     * @details this method is `generic`, and has a constant template.
     * @throws std::runtime_error if the `input` is in an `illegal` format.
     */
    template<typename T>
    static T
    getChecked(std::istream &                            is,
               const std::function<bool(std::string &)> &checkingFunction,
               const std::function<T(const char *)> &    returnFunction) {

        // `getChecked` the input.
        std::string stringInput;
        std::getline(is, stringInput);
        if (checkingFunction(stringInput)) {

            // if this is a legal input, return it.
            return returnFunction(stringInput.c_str());
        } else {
            throw std::runtime_error("wrong input");
        }
    }

    /* -- Checkers -- */
  private:
    /**
     * @brief This method receives as a parameter a `std::string` and checks
     *        whether it is a legal **Int**.
     *
     * This method is *private*, and is being used as a parameter for the
     * invocation of @link getCheckedInt(std::string &) @endlink in
     * the body of @link getChecked @endlink method.
     * @param input the `input` gotten, that is needed to be checked.
     * @return @li `true` if the `input` is `legal / valid`.
     *         @li `false` if the `input` is `illegal / invalid`.
     * @see getCheckedInt(std::istream &)
     * @see getChecked
     */
    static bool checkIntInput(std::string &input);

    /**
     * @brief This method receives as a parameter a `std::string` and checks
     *        whether it is a legal **UnsignedInt**.
     *
     * This method is *private*, and is being used as a parameter for the
     * invocation of @link getCheckedUnsignedInt(std::string &) @endlink in
     * the body of @link getChecked @endlink method.
     * @param input the `input` gotten, that is needed to be checked.
     * @return @li `true` if the `input` is `legal / valid`.
     *         @li `false` if the `input` is `illegal / invalid`.
     * @see getCheckedUnsignedInt(std::istream &)
     * @see getChecked
     */
    static bool checkUnsignedIntInput(std::string &input);

    /**
     * @brief This method receives as a parameter a `std::string` and checks
     *        whether it is a legal **PositiveInt**.
     *
     * This method is *private*, and is being used as a parameter for the
     * invocation of @link getCheckedPositiveInt(std::string &) @endlink in
     * the body of @link getChecked @endlink method.
     * @param input the `input` gotten, that is needed to be checked.
     * @return @li `true` if the `input` is `legal / valid`.
     *         @li `false` if the `input` is `illegal / invalid`.
     * @see getCheckedPositiveInt(std::istream &)
     * @see getChecked
     */
    static bool checkPositiveIntInput(std::string &input);
};

#endif //MIVNEI_NETUNIM_EX2_INPUTOUTPUT_H
