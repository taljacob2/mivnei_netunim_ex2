
#ifndef MIVNEI_NETUNIM_EX2_INPUTOUTPUT_H
#define MIVNEI_NETUNIM_EX2_INPUTOUTPUT_H

#include "my_algorithms.h"
#include "my_string.h"
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

    my_string _input;

    /// The name of the 'Measure' file:
    static constexpr char *fileName = (char *) "Measure.txt";


    static bool checkLegalUnsignedIntInput(my_string &input);

    static bool checkLegalDoubleInput(my_string &input);

    static bool checkLegalIntInput(my_string &input);

    int getSize();

    /**
     * @brief this method gets the `serialSizeOfTheElementToLookFor` from the user.
     *
     * @note the `index` of the `serialSizeOfTheElementToLookFor`
     *       is actually `serialSizeOfTheElementToLookFor - 1`.
     * @param size size of the array to search in.
     * @return serialSizeOfTheElementToLookFor
     * @throws std::range_error if `serialSizeOfTheElementToLookFor` is out of range.
     * @throws std::runtime_error if the `input` is in an illegal format.
     */
    int getSerialSizeOfTheElementToLookFor(int size);

    void setArrayContents(double array[], int size);

  public:
    InputOutput(int &N, int &K, std::string &inputFileName,
                std::string &outputFileName)
        : N(N), K(K), INPUT_FILE_NAME(inputFileName),
          OUTPUT_FILE_NAME(outputFileName) {

        // sets the floating point precision of whole "cout" stream:
        std::cout << std::setprecision(4);
        std::cout << std::fixed;
    }

    ~InputOutput();

    /* -- Getters & Setters -- */

    int                getN() const;
    int                getK() const;
    const std::string &getInputFileName() const;
    const std::string &getOutputFileName() const;

    /**
     * @brief gets all inputs from the user.
     *
     * @param size the size of the array.
     * @param serialSizeOfTheElementToLookFor the index to be searched.
     * @return the `new` created array.
     * @throws std::runtime_error
     * @throws std::range_error
     */
    double *getAllInputs(int &size,
                         int &serialSizeOfTheElementToLookFor) noexcept(false);

    /**
     * this *static* method measures the time it takes
     * to a given @p functionToMeasure
     * to work on the @p array given.
     * the method outputs the measures to the
     * `this::fileName` `Measure` file.
     *
     * @tparam T element of the array.
     * @param array array to be manipulated.
     * @param size size of the given array.
     * @param functionToMeasure the method that manipulates the array.
     * @return the `new` allocated manipulated array.
     * @see my_algorithms
     * @see `this::fileName`
     */
    template<class T>
    static T *printMeasure(
            T *array, int size,
            const std::function<void(T *, int, char *&)> &functionToMeasure) {

        // copy the array to another array:
        T *arrayToManipulate = my_algorithms::copyArray(array, size);

        // get the function name:
        char *nameOfFunctionToMeasure;

        auto start = std::chrono::high_resolution_clock::now();

        // unsync the I/O of C and C++.
        std::ios_base::sync_with_stdio(false);

        // Here you put the name of the function you wish to measure:
        functionToMeasure(arrayToManipulate, size, nameOfFunctionToMeasure);
        auto end = std::chrono::high_resolution_clock::now();

        // Calculating total time taken by the program.
        calculateTotalTimeTakenByTheProgram(start, end,
                                            nameOfFunctionToMeasure);

        // return the manipulated array:
        return arrayToManipulate;
    }

    /**
    * this *static* method measures the time it takes
    * to a given @p functionToMeasure
    * to work on the @p array given.
    * the method outputs the measures to the
    * `this::fileName` `Measure` file.
    *
    * @tparam T element of the array.
    * @param array array to be manipulated.
    * @param size size of the given array.
    * @param functionToMeasure the method that manipulates the array.
    * @return the `new` allocated manipulated array.
    * @see my_algorithms
    * @see `this::fileName`
    */
    template<class T>
    static T printMeasure(
            T *array, int size, int serialSizeOfTheElementToLookFor,
            const std::function<T(T *, int, int, char *&)> &functionToMeasure) {

        // copy the array to another array:
        T *arrayToManipulate = my_algorithms::copyArray(array, size);

        // get the function name:
        char *nameOfFunctionToMeasure;

        auto start = std::chrono::high_resolution_clock::now();

        // unsync the I/O of C and C++.
        std::ios_base::sync_with_stdio(false);

        // Here you put the name of the function you wish to measure:
        auto elementRequested = functionToMeasure(
                arrayToManipulate, size, serialSizeOfTheElementToLookFor,
                nameOfFunctionToMeasure);
        auto end = std::chrono::high_resolution_clock::now();

        // Calculating total time taken by the program.
        calculateTotalTimeTakenByTheProgram(start, end,
                                            nameOfFunctionToMeasure);

        // delete copied array:
        delete[] arrayToManipulate;

        // return the manipulated array:
        return elementRequested;
    }

    template<class T>
    static void setSorts(T *array, int size,
                         int serialSizeOfTheElementToLookFor,
                         T *&insertionSortedArray, T &selectionElementRequested,
                         T &quintupletElementRequested) {

        // insertion-sort:
        insertionSortedArray = InputOutput::printMeasure<double>(
                array, size, my_algorithms::sort_insertion_<double>);

        // selection:
        selectionElementRequested = InputOutput::printMeasure<double>(
                array, size, serialSizeOfTheElementToLookFor,
                my_algorithms::selection_TheIthElementInItsSize_<double>);

        // quintuplet:
        quintupletElementRequested = InputOutput::printMeasure<double>(
                array, size, serialSizeOfTheElementToLookFor,
                my_algorithms::quintuplet_TheIthElementInItsSize_<double>);
    }

    template<class T>
    static void printElements(T * insertionSortedArray,
                              T & selectionElementRequested,
                              T & quintupletElementRequested,
                              int serialSizeOfTheElementToLookFor) {

        // insertion:
        std::cout << "Insertion sort i'th element: ";
        std::cout << insertionSortedArray[serialSizeOfTheElementToLookFor - 1]
                  << std::endl;

        // selection:
        std::cout << "Selection i'th element: ";
        std::cout << selectionElementRequested << std::endl;

        // quintuplet:
        std::cout << "Quintuplet algorithm i'th element: ";
        std::cout << quintupletElementRequested << std::endl;
    }

  private:
    static void calculateTotalTimeTakenByTheProgram(
            std::chrono::time_point<std::chrono::high_resolution_clock> start,
            std::chrono::time_point<std::chrono::high_resolution_clock> end,
            const char *nameOfFunctionToMeasure) {

        // Calculating total time taken by the program.
        double time_taken =
                std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                     start)
                        .count();
        time_taken *= 1e-9;

        // The name of the file, append writing:
        std::ofstream file(fileName, std::ios_base::app);
        file << "Time taken by function " << nameOfFunctionToMeasure
             << " is : " << std::setprecision(9) << std::fixed << time_taken;
        file << " sec" << std::endl;
        file.close();
    }

  public:
    static void receiveInput(int &N, int &K, std::string &inputFileName,
                             std::string &outputFileName) {

        /* Receive N */
        std::cin >> N;

        /* Receive K */
        std::cin >> K;

        /* Receive name of InputFile: */
        std::cin >> inputFileName;

        /* Receive name of OutputFile: */
        std::cin >> outputFileName;
    }

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
    static InputOutput *factoryInputOutput() {

        /* Receive input: */
        int         N;
        int         K;
        std::string INPUT_FILE_NAME;
        std::string OUTPUT_FILE_NAME;
        InputOutput::receiveInput(N, K, INPUT_FILE_NAME, OUTPUT_FILE_NAME);

        /* Create InputOutput object */
        return new InputOutput(N, K, INPUT_FILE_NAME, OUTPUT_FILE_NAME);
    }

    /**
     * @brief This method gets the `array` specified in the *INPUT_FILE*
     *        provided by the *INPUT_FILE_NAME*.
     *
     * @return the *int* array specified in the *INPUT_FILE* .
     * @throws std::runtime_error in case the *file* specified by the
     *         name: `INPUT_FILE_NAME` could not be found.
     */
    int *getIntArrayFromInputFile() {
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
        while (i < N) {
            try {
                array[i] = getInt(file);
            } catch (std::exception &e) {
                delete[] array;
                throw;
            }
            i++;
        }
        // TODO: check the loop stop condition - check `eof`?

        file.close();
        return array;
    }

    int         getUnsignedInt(std::istream &is, int size);
    int         getInt(std::istream &is);
    static bool checkLegalIntInput(std::string &input);
};

#endif //MIVNEI_NETUNIM_EX2_INPUTOUTPUT_H
