//
// Created by Tal on 26-Mar-21.
//

#ifndef MIVNEI_NETUNIM_EX1_INPUTOUTPUT_H
#define MIVNEI_NETUNIM_EX1_INPUTOUTPUT_H

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
    my_string _input;

    /// The name of the 'Measure' file:
    static constexpr char *fileName = (char *) "Measure.txt";

    static bool checkLegalUnsignedIntInput(my_string &input);

    static bool checkLegalDoubleInput(my_string &input);

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
    InputOutput();

    ~InputOutput();

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
};

#endif //MIVNEI_NETUNIM_EX1_INPUTOUTPUT_H
