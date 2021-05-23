
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
    const long int N;

    /**
     * The division parameter - to how many `small arrays` the
     * `given array` would be divided.
     */
    const long int K;

    /// The name of the `input` file.
    const std::string INPUT_FILE_NAME;

    /// The name of the `output` file.
    const std::string OUTPUT_FILE_NAME;

    /* -- Constructor & Destructor -- */
  public:
    InputOutput(long int &N, long int &K, std::string &inputFileName,
                std::string &outputFileName);

    ~InputOutput();

    /* -- Getters -- */
  public:
    long int           getN() const;
    long int           getK() const;
    const std::string &getInputFileName() const;
    const std::string &getOutputFileName() const;

    /* -- Main Methods -- */
  public:
    /**
     *
     * @param N the size of the array in the `input` file.
     * @param K the division parameter - to how many `small arrays` the
     *          `given array` would be divided.
     * @param inputFileName
     * @param outputFileName
     * @throws std::runtime_error if an `input` is in an `illegal` format.
     */
    static void receiveInput(long int &N, long int &K,
                             std::string &inputFileName,
                             std::string &outputFileName);

    /**
     * @brief This method serves as a **Factory** method.
     *
     * Receives input:
     *      @li (long int) N - the number of elements provided.
     *      @li (long int) K - the division parameter - to how many `small arrays`
     *                    the `given array` would be divided.
     *      @li (std::string) INPUT_FILE_NAME - the name of the `inputFile`.
     *      @li (std::string) OUTPUT_FILE_NAME - the name of the `outputFile`.
     *
     * Construction:
     *      @li Constructs a `new` *InputOutput* object from the given input, and
     *      returns it.
     * @return Constructs a `new` *InputOutput* object from the given input,
     *         and returns it.
     * @throws std::runtime_error if an `input` is in an `illegal` format,
     *         when receiving input in the `receiveInput` method.
     * @see InputOutput(long int&, long int&, std::string&, std::string&)
     * @see receiveInput(long int &, long int &, std::string &, std::string &)
     */
    static InputOutput *factoryInputOutput();

    /**
     * @brief This method gets the `array` specified in the *INPUT_FILE*
     *        provided by the *INPUT_FILE_NAME*.
     *
     * @return the *long int* array specified in the *INPUT_FILE* .
     * @throws std::runtime_error @li in case the *file* specified by the
     *                            name: `INPUT_FILE_NAME` could not be found.
     *                            @li in case the `N` provided in the *file*
     *                            is larger than the actual number of elements
     *                            provided in the *file*.
     */
    long int *getLongIntArrayFromInputFile();

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
    static void printArray(std::ostream &os, T *array, long int size) {
        for (long int i = 0; i < size; i++) { os << array[i] << " "; }
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
    static void printArray(std::ostream &os, T *array, long int size,
                           char delimiter) {
        long int i = 0;
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
                                 long int size) {
        std::ofstream file(outputFileName);
        if (!file) {

            /* Could not open the file. Throw a message. */
            // std::string message;
            // message.append("Could not open the file: ");
            // message.append(outputFileName);
            // message.append("\n");

            throw std::runtime_error("wrong input");
        }

        for (long int i = 0; i < size; i++) { file << array[i] << " "; }
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
                                 long int size, char delimiter) {
        std::ofstream file(outputFileName);
        if (!file) {

            /* Could not open the file. Throw a message. */
            // std::string message;
            // message.append("Could not open the file: ");
            // message.append(outputFileName);
            // message.append("\n");

            throw std::runtime_error("wrong input");
        }
        long int i = 0;
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
    template<typename T> void printArrayToFile(T *array, long int size) {
        std::ofstream file(OUTPUT_FILE_NAME);
        if (!file) {

            /* Could not open the file. Throw a message. */
            // std::string message;
            // message.append("Could not open the file: ");
            // message.append(OUTPUT_FILE_NAME);
            // message.append("\n");

            throw std::runtime_error("wrong input");
        }

        for (long int i = 0; i < size; i++) { file << array[i] << " "; }
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
    void printArrayToFile(T *array, long int size, char delimiter) {
        std::ofstream file(OUTPUT_FILE_NAME);
        if (!file) {

            /* Could not open the file. Throw a message. */
            // std::string message;
            // message.append("Could not open the file: ");
            // message.append(OUTPUT_FILE_NAME);
            // message.append("\n");

            throw std::runtime_error("wrong input");
        }
        long int i = 0;
        for (; i < size - 1; i++) { file << array[i] << delimiter; }
        file << array[i];
        file.close();
    }

    /* -- Get Checkers -- */
  public:
    /**
     * @brief This method receives an `input` from an `input-stream` and checks
     *        whether it is a legal **LongInt**.
     *
     * @li In case the `input` gotten is `legal / valid`, return in.
     * @li In case the `input` gotten is `illegal / invalid`, throw an
     * exception.
     * @param is the `input-stream` to get the `input` from.
     * @return the `input` gotten from the `input-stream` @p is, after
     *         passing the checking validation.
     * @throws std::runtime_error if the `input` is in an `illegal` format.
     * @see checkLongIntInput(std::string &)
     * @see getChecked
     */
    static long int getCheckedLongInt(std::istream &is);

    /**
     * @brief This method receives an `input` from an `input-stream` and checks
     *        whether it is a legal **UnsignedLongInt**.
     *
     * @li In case the `input` gotten is `legal / valid`, return in.
     * @li In case the `input` gotten is `illegal / invalid`, throw an
     * exception.
     * @param is the `input-stream` to get the `input` from.
     * @return the `input` gotten from the `input-stream` @p is, after
     *         passing the checking validation.
     * @throws std::runtime_error if the `input` is in an `illegal` format.
     * @see checkUnsignedLongIntInput(std::string &)
     * @see getChecked
     */
    static long int getCheckedUnsignedLongInt(std::istream &is);

    /**
     * @brief This method receives an `input` from an `input-stream` and checks
     *        whether it is a legal **PositiveLongInt**.
     *
     * @li In case the `input` gotten is `legal / valid`, return in.
     * @li In case the `input` gotten is `illegal / invalid`, throw an
     * exception.
     * @param is the `input-stream` to get the `input` from.
     * @return the `input` gotten from the `input-stream` @p is, after
     *         passing the checking validation.
     * @throws std::runtime_error if the `input` is in an `illegal` format.
     * @see checkPositiveLongIntInput(std::string &)
     * @see getChecked
     */
    static long int getCheckedPositiveLongInt(std::istream &is);

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
     *        whether it is a legal **LongInt**.
     *
     * This method is *private*, and is being used as a parameter for the
     * invocation of @link getCheckedLongInt(std::string &) @endlink in
     * the body of @link getChecked @endlink method.
     * @param input the `input` gotten, that is needed to be checked.
     * @return @li `true` if the `input` is `legal / valid`.
     *         @li `false` if the `input` is `illegal / invalid`.
     * @see getCheckedLongInt(std::istream &)
     * @see getChecked
     */
    static bool checkLongIntInput(std::string &input);

    /**
     * @brief This method receives as a parameter a `std::string` and checks
     *        whether it is a legal **UnsignedLongInt**.
     *
     * This method is *private*, and is being used as a parameter for the
     * invocation of @link getCheckedUnsignedLongInt(std::string &) @endlink in
     * the body of @link getChecked @endlink method.
     * @param input the `input` gotten, that is needed to be checked.
     * @return @li `true` if the `input` is `legal / valid`.
     *         @li `false` if the `input` is `illegal / invalid`.
     * @see getCheckedUnsignedLongInt(std::istream &)
     * @see getChecked
     */
    static bool checkUnsignedLongIntInput(std::string &input);

    /**
     * @brief This method receives as a parameter a `std::string` and checks
     *        whether it is a legal **PositiveLongInt**.
     *
     * This method is *private*, and is being used as a parameter for the
     * invocation of @link getCheckedPositiveLongInt(std::string &) @endlink in
     * the body of @link getChecked @endlink method.
     * @param input the `input` gotten, that is needed to be checked.
     * @return @li `true` if the `input` is `legal / valid`.
     *         @li `false` if the `input` is `illegal / invalid`.
     * @see getCheckedPositiveLongInt(std::istream &)
     * @see getChecked
     */
    static bool checkPositiveLongIntInput(std::string &input);
};

#endif //MIVNEI_NETUNIM_EX2_INPUTOUTPUT_H
