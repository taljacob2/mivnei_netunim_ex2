
#ifndef MIVNEI_NETUNIM_EX2_MY_ALGORITHMS_H
#define MIVNEI_NETUNIM_EX2_MY_ALGORITHMS_H


#include <cmath>
#include <exception>
#include <functional>
#include <iostream>


/**
 * @brief this class bundles together all the algorithm
 *        methods in the program.
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 2.0
 */
class my_algorithms {
  public:
    /**
     * @brief Compares two elements pointed out from two pointers, by their
     *        given indexes, and returns the index to the pointer that points
     *        to the larger element out of them.
     *
     * The method ensures safety:
     * @li The method makes sure to ensure that the @p indexToElement1 and @p
     * indexToElement2 provided are not out of range.
     * @li The method makes sure to ensure that the elements are not
     * `nullptr`, and if they are `nullptr`, the method knows how to handle
     * them.
     * @note if element is a `nullptr`, prioritize to return the index of the
     *       *other* element given.
     *       If both element are `nullptr`, return the index of the *first*
     *       element.
     * @attention if @p indexToElement2 is out fo range, but @p
     *            indexToElement1 is not out of range, the method returns the
     *            @p indexToElement1.
     * @param array an array of pointers to elements.
     * @param indexToElement1 index of pointer to first element to compare.
     * @param indexToElement2 index of pointer to second element to compare.
     * @return the index of the pointer that points to the larger element.
     * @throws std::out_of_range in case *both* of the indexes
     *         @p indexToElement1 and @p indexToElement2 provided are
     *         out of range.
     */
    template<class T>
    static int max(T **array, int size, int indexToElement1,
                   int indexToElement2) {
        if (((indexToElement2 < size) && (0 <= indexToElement2)) &&
            ((indexToElement1 < size) && (0 <= indexToElement1))) {

            /*
             * If `indexToElement2` is not out-of-range.
             * and `indexToElement1` is not out-of-range.
             */
            if (array[indexToElement2] == nullptr) {
                return indexToElement1;
            } else if (array[indexToElement2] != nullptr) {
                if (array[indexToElement1] == nullptr) {
                    return indexToElement2;
                } else {

                    // Both elements are not nullptr. Compare regularly.
                    return (*array[indexToElement1]) > (*array[indexToElement2])
                                   ? indexToElement1
                                   : indexToElement2;
                }
            }
        } else if ((indexToElement1 < size) && (0 <= indexToElement1)) {

            /* If `indexToElement1` is not out-of-range. */
            return indexToElement1;
        }

        /*
         * Both `indexToElement1` and `indexToElement2` are out-of-range.
         * Throw a message.
         */
        std::string message;
        message.append("Both of the indexes provided are out of range. "
                       "There are ");
        message.append(std::to_string(size));
        message.append(" elements in the array.\n");

        // TODO: change to `wrong input`
        throw std::out_of_range(message);
    }

    /**
     * @brief Compares two elements pointed out from two pointers, by their
     *        given indexes, and returns the index to the pointer that points
     *        to the smaller element out of them.
     *
     * The method ensures safety:
     * @li The method makes sure to ensure that the @p indexToElement1 and @p
     * indexToElement2 provided are not out of range.
     * @li The method makes sure to ensure that the elements are not
     * `nullptr`, and if they are `nullptr`, the method knows how to handle
     * them.
     * @note if element is a `nullptr`, prioritize to return the index of the
     *       *other* element given.
     *       If both element are `nullptr`, return the index of the *first*
     *       element.
     * @attention if @p indexToElement2 is out fo range, but @p
     *            indexToElement1 is not out of range, the method returns the
     *            @p indexToElement1.
     * @param array an array of pointers to elements.
     * @param indexToElement1 index of pointer to first element to compare.
     * @param indexToElement2 index of pointer to second element to compare.
     * @return the index of the pointer that points to the smaller element.
     * @throws std::out_of_range in case *both* of the indexes
     *         @p indexToElement1 and @p indexToElement2 provided are
     *         out of range.
     */
    template<class T>
    static int min(T **array, int size, int indexToElement1,
                   int indexToElement2) {
        if (((indexToElement2 < size) && (0 <= indexToElement2)) &&
            ((indexToElement1 < size) && (0 <= indexToElement1))) {

            /*
             * If `indexToElement2` is not out-of-range.
             * and `indexToElement1` is not out-of-range.
             */
            if (array[indexToElement2] == nullptr) {
                return indexToElement1;
            } else if (array[indexToElement2] != nullptr) {
                if (array[indexToElement1] == nullptr) {
                    return indexToElement2;
                } else {

                    // Both elements are not nullptr. Compare regularly.
                    return (*array[indexToElement1]) < (*array[indexToElement2])
                                   ? indexToElement1
                                   : indexToElement2;
                }
            }
        } else if ((indexToElement1 < size) && (0 <= indexToElement1)) {

            /* If `indexToElement1` is not out-of-range. */
            return indexToElement1;
        }

        /*
         * Both `indexToElement1` and `indexToElement2` are out-of-range.
         * Throw a message.
         */
        std::string message;
        message.append("Both of the indexes provided are out of range. "
                       "There are ");
        message.append(std::to_string(size));
        message.append(" elements in the array.\n");

        // TODO: change to `wrong input`
        throw std::out_of_range(message);
    }

    /**
     * @brief generic algorithm to copy an array.
     *
     * @returns the `new` copied array.
     */
    template<class T> static T *copyArray(const T *array, int size) {
        auto *copiedArr = new T[size];
        for (int i = 0; i < size; ++i) { copiedArr[i] = array[i]; }
        return copiedArr;
    }

    /**
     * @brief generic `swap` algorithm of two elements in an array.
     *
     * @tparam T elements to be swapped.
     * @param array the array which contains the elements.
     * @param index1 the first element index to be swapped.
     * @param index2 the second element index to be swapped.
     */
    template<class T> static void swap(T *array, int index1, int index2) {
        T tmp         = array[index1];
        array[index1] = array[index2];
        array[index2] = tmp;
    }

    /**
     * @brief generic `swap` algorithm of two elements.
     *
     * @tparam T elements to be swapped.
     * @param element1 first element.
     * @param element2 second element.
     */
    template<class T> static void swap(T &element1, T &element2) {
        T tmp    = element1;
        element1 = element2;
        element2 = tmp;
    }

    /**
     * @brief sorts the array given array.
     *
     * @param array
     * @param size the size of the array.
     */
    template<class T> static void sort_insertion(T *array, int size) {
        if (size <= 1) { return; }

        for (int head_index = 1; head_index < size; ++head_index) {
            int curr_head_index = head_index;
            for (int predecessor_index = head_index - 1; predecessor_index >= 0;
                 predecessor_index--) {
                if ((array)[predecessor_index] > (array)[curr_head_index]) {
                    swap<T>((array), curr_head_index, predecessor_index);
                    curr_head_index = predecessor_index;
                } else {
                    break;
                }
            }
        }
    }

    /**
     * @brief this method is made for getting the
     *        `sort_insertion_` method name by reflection.
     *
     * @param outputParameterForThisFunctionName output parameter
     *                                           to getChecked this function's name.
     * @see sort_insertion (E *, int)
     */
    template<class T>
    static void sort_insertion_(T *array, int size,
                                char *&outputParameterForThisFunctionName) {

        // getChecked this function's name:
        outputParameterForThisFunctionName = const_cast<char *>(__func__);
        sort_insertion(array, size);
    }

    /**
     * @brief sorts a specific element in the array, named as `pivot`,
     *        and returns its index.
     *
     * @warning this method doesn't check that the
     *          @p lowestIndexPossible and @p highestIndexPossible
     *          are valid indexes in the array.
     * @note by default, this method places the `pivot` in the **earliest**
     *       index possible.
     * @tparam T element of the array.
     * @param array the array to be sorted.
     * @param lowestIndexPossible the lowest index in the @p array given.
     * @param highestIndexPossible the highest index in the @p array given.
     * @param indexOfElementToServeAsPivot it is possible to insert here the
     *                                     desired `index` for the `pivot`
     *                                     to be found.
     * @returns the pivot's index.
     * @see swap(E *, int, int) - for swapping the elements in the array.
     * @see swap(E &, E &) - for swapping the elements' indexes in the array.
     */
    template<class T>
    static int partition(T *array, int lowestIndexPossible,
                         int highestIndexPossible,
                         int indexOfElementToServeAsPivot = 0) {

        /*
         * set initial-`pivotIndex` to be the `first` `element` in the array,
         * thus set the `nonPivotIndex` to be the `last` in the array.
         * This is set arbitrarily, but is not necessarily important.
         */
        int pivotIndex = lowestIndexPossible;
        if (indexOfElementToServeAsPivot != 0) {

            /*
             * if there is a request to know the specific `pivot-index`
             * of a specific-given `index`, set the `element` of this
             * specific-given `index` to be the initial-`pivot-element`.
             */
            swap<T>(array, pivotIndex, indexOfElementToServeAsPivot);
        }
        int nonPivotIndex = highestIndexPossible;

        while (true) {
            if (pivotIndex < nonPivotIndex) {
                if (array[pivotIndex] > array[nonPivotIndex]) {
                    swap<T>(array, pivotIndex, nonPivotIndex);
                    swap<int>(pivotIndex, nonPivotIndex);
                    ++nonPivotIndex;
                } else {
                    --nonPivotIndex;
                }
            } else if (nonPivotIndex < pivotIndex) {
                if (array[nonPivotIndex] > array[pivotIndex]) {
                    swap<T>(array, pivotIndex, nonPivotIndex);
                    swap<int>(pivotIndex, nonPivotIndex);
                    --nonPivotIndex;
                } else {
                    ++nonPivotIndex;
                }
            } else if (nonPivotIndex == pivotIndex) {
                return pivotIndex;
            }
        }
    }

    /**
     * @brief this method is the *public* method for the
     *        *selectTheIthElementInItsSize_UnSecured* method.
     *
     * implemented with the **secured** *constant* parameters:
     * @tparam T element of the array.
     * @param array the array to be searched.
     * @param size the size of the given @p array.
     * @param serialSizeOfTheElementToLookFor The **serial size** of the element to look for.
     * @return the *value* of the element which
     *         @p serialSizeOfTheElementToLookFor is its **serial size**.
     * @see  selectTheIthElementInItsSize_UnSecured(E *, int, int, int)
     */
    template<class T>
    static T
    selection_TheIthElementInItsSize(T *array, int size,
                                     int serialSizeOfTheElementToLookFor) {
        return selectTheIthElementInItsSize_UnSecured(
                array, 0, size - 1, serialSizeOfTheElementToLookFor);
    }

    /**
     * @brief this method is made for getting the
     *        `selectTheIthElementInItsSize_` method name by reflection.
     *
     * @param outputParameterForThisFunctionName output parameter
     *                                           to getChecked this function's name.
     * @see selection_TheIthElementInItsSize (E *, int, int)
     */
    template<class T>
    static T selection_TheIthElementInItsSize_(
            T *array, int size, int serialSizeOfTheElementToLookFor,
            char *&outputParameterForThisFunctionName) {

        // getChecked this function's name:
        outputParameterForThisFunctionName = const_cast<char *>(__func__);
        return selection_TheIthElementInItsSize(
                array, size, serialSizeOfTheElementToLookFor);
    }

    /**
     * @brief sorts an array using the `bubble-sort` algorithm.
     *
     * @tparam T element of the array.
     * @param array the array to be sorted.
     * @param size the size of the given @p array.
     */
    template<class T> static void bubbleSort(T *array, int size) {
        for (int i = 0; i < size; ++i) {
            for (int j = size - 1; j > i; --j) {
                if (array[i] > array[j]) { swap(array, i, j); }
            }
        }
    }

    /**
     * @brief this method searches for the `I'th element in its size`
     *        by giving a parameter of @p serialSizeOfTheElementToLookFor.
     *
     * @tparam T element of the array.
     * @tparam DIVISION set here the Division you would like.
     * @param array the array to be sorted.
     * @param size the size of the given @p array.
     * @param serialSizeOfTheElementToLookFor
     * @return the *value* of the element which
     *         @p serialSizeOfTheElementToLookFor is its **serial size**.
     */
    template<class T, int DIVISION>
    static T
    division_TheIthElementInItsSize(T *array, int size,
                                    int serialSizeOfTheElementToLookFor) {
        if (size <= DIVISION) {
            bubbleSort(array, size);
            return array[serialSizeOfTheElementToLookFor - 1];
        } else {
            int divisionCounter      = 1;
            int lastDividedArraySize = DIVISION;
            int divisionInteger      = 1;
            whileOfBubbleSort_division_TheIthElementInItsSize<T, DIVISION>(
                    array, size, divisionCounter, divisionInteger,
                    lastDividedArraySize);
            T *takenMiddlesArray = new T[divisionCounter];
            getMiddleArray_division_TheIthElementInItsSize<T, DIVISION>(
                    array, takenMiddlesArray, divisionCounter,
                    lastDividedArraySize);
            int k_index;
            try {
                getTakenMiddlesArrayPivotElementAndIndex_division_TheIthElementInItsSize<
                        T, DIVISION>(array, size, takenMiddlesArray,
                                     divisionCounter, k_index);
            } catch (std::exception &e) { return 0; }
            delete[] takenMiddlesArray;
            return returnOf_division_TheIthElementInItsSize<T, DIVISION>(
                    array, size, serialSizeOfTheElementToLookFor, k_index);
        }
    }

    /**
     * implements `quintuplet_TheIthElementInItsSize` as @e DIVISION = 5.
     * @see quintuplet_TheIthElementInItsSize (E *, int, int)
     */
    template<class T>
    static T
    quintuplet_TheIthElementInItsSize(T *array, int size,
                                      int serialSizeOfTheElementToLookFor) {
        return division_TheIthElementInItsSize<T, 5>(
                array, size, serialSizeOfTheElementToLookFor);
    }

    /**
     * @brief this method is made for getting the
     *        `sort_quintuplet_` method name by reflection.
     *
     * @param outputParameterForThisFunctionName output parameter
     *                                           to getChecked this function's name.
     * @see quintuplet_TheIthElementInItsSize (E *, int, int)
     */
    template<class T>
    static T quintuplet_TheIthElementInItsSize_(
            T *array, int size, int serialSizeOfTheElementToLookFor,
            char *&outputParameterForThisFunctionName) {

        // getChecked this function's name:
        outputParameterForThisFunctionName = const_cast<char *>(__func__);
        return quintuplet_TheIthElementInItsSize<T>(
                array, size, serialSizeOfTheElementToLookFor);
    }

  private:
    template<class T, int DIVISION>
    static void whileOfBubbleSort_division_TheIthElementInItsSize(
            T *array, int size, int &divisionCounter, int &divisionInteger,
            int &lastDividedArraySize) {
        while (divisionInteger >= 1) {
            divisionInteger = (size / (divisionCounter * DIVISION));
            if (divisionInteger < 1) {

                // this is the last division, doesn't divide completely:
                lastDividedArraySize =
                        size - ((divisionCounter - 1) * DIVISION);
            }

            // sort each divided array with bubble-sort:
            bubbleSort(array + ((divisionCounter - 1) * DIVISION),
                       lastDividedArraySize);
            ++divisionCounter;
        }

        // always remove the last counter.
        --divisionCounter;
        if (lastDividedArraySize == 0) {

            // if there is no left-over, remove the last counter:
            --divisionCounter;
        }
    }

    template<class T, int DIVISION>
    static void getMiddleArray_division_TheIthElementInItsSize(
            T *array, T *takenMiddlesArray, int divisionCounter,
            int lastDividedArraySize) {
        int i = 0;
        for (; i < divisionCounter - 1; ++i) {

            /*
             * getChecked middleElement in each divided-array,
             * and insert it to `takenMiddlesArray`:
             */
            takenMiddlesArray[i] = getMiddleElementInASortedArray(
                    array + (i * DIVISION), DIVISION);
        }

        // getChecked middleElement from the last leftOver array (special case):
        takenMiddlesArray[i] = getMiddleElementInASortedArray(
                array + (i * DIVISION), lastDividedArraySize);
    }

    template<class T, int DIVISION>
    static void
    getTakenMiddlesArrayPivotElementAndIndex_division_TheIthElementInItsSize(
            T *array, int size, T *takenMiddlesArray, int divisionCounter,
            int &takenMiddlesArray_medianPivotElement_indexInArray) {

        /*
         * getting the median in `takenMiddlesArray`,
         * with a `recursive` call:
         */
        T takenMiddlesArray_medianPivotElement =
                division_TheIthElementInItsSize<T, DIVISION>(
                        takenMiddlesArray, divisionCounter,
                        ((divisionCounter - 1) / 2) + 1);

        // search for the `takenMiddlesArray_medianPivotElement` index in `array`:
        takenMiddlesArray_medianPivotElement_indexInArray = 0;
        for (; takenMiddlesArray_medianPivotElement_indexInArray < size;
             ++takenMiddlesArray_medianPivotElement_indexInArray) {
            if (array[takenMiddlesArray_medianPivotElement_indexInArray] ==
                takenMiddlesArray_medianPivotElement) {
                break;
            }
        }

        /*
         * if we didn't find `takenMiddlesArray_medianPivotElement`
         * index in `array`, throw. --- this shouldn't happen!
         */
        if (array[takenMiddlesArray_medianPivotElement_indexInArray] !=
            takenMiddlesArray_medianPivotElement) {
            std::cerr << "ERROR: could not find "
                      << takenMiddlesArray_medianPivotElement
                      << " in the `takenMiddlesArray`." << std::endl;
            throw std::exception();
        }

        /*
         * partition the `array` based on the
         * `takenMiddlesArray_medianPivotElement_indexInArray` we have found
         * to be the k_index in the `array`:
         */
        takenMiddlesArray_medianPivotElement_indexInArray =
                partition(array, 0, size - 1,
                          takenMiddlesArray_medianPivotElement_indexInArray);
    }

    template<class T, int DIVISION>
    static T returnOf_division_TheIthElementInItsSize(T *array, int size, int i,
                                                      int k_index) {
        int i_index = i - 1;

        if (i_index < k_index) {
            return division_TheIthElementInItsSize<T, DIVISION>(array, k_index,
                                                                i);
        } else if (k_index < i_index) {
            return division_TheIthElementInItsSize<T, DIVISION>(
                    array + (k_index + 1), size - (k_index + 1),
                    (i_index - k_index));
        } else if (i_index == k_index) {

            // return the value of the i'th element in its size.
            return array[k_index];
        }
        return 0; // ERROR CASE
    }

    /**
     * @brief this method searches for the `I'th element in its size`
     *        by giving a parameter of @p serialSizeOfTheElementToLookFor.
     *
     * Recursively implemented.
     *
     * @attention this method *modifies* the given @p array
     *            and ruins it in order to make the search.
     * @tparam T element of the array.
     * @param array the array to be sorted.
     * @param lowestIndexToSearchAt the highest index to search the
     *                              `I'th element in its size` at `pivot` index
     *                               (*including* the `pivot` index).
     * @param highestIndexToSearchAt size of the @p array given -
     *                               derives the high partition to the `pivot`
     *                               index (*excluding* the `pivot` index).
     * @param serialSizeOfTheElementToLookFor The **serial size** of the
     *                                        element to look for.
     * @return the *value* of the element which
     *         @p serialSizeOfTheElementToLookFor is its **serial size**.
     * @see partition(E *, int, int)
     * @see selectTheIthElementInItsSize(E *, int, int)
     */
    template<class T>
    static T selectTheIthElementInItsSize_UnSecured(
            T *array, int lowestIndexToSearchAt, int highestIndexToSearchAt,
            int serialSizeOfTheElementToLookFor) {

        // getChecked a pivotIndex:
        int pivotIndex =
                partition(array, lowestIndexToSearchAt, highestIndexToSearchAt);

        // note the `+1` to include the `pivot` element in the lowPartition:
        int lowPartitionSize = pivotIndex - lowestIndexToSearchAt + 1;

        // the `pivot` is the element we have searched for, thus return it:
        if (serialSizeOfTheElementToLookFor == lowPartitionSize) {
            return array[pivotIndex];
        }

        /*
         * otherwise, search the nearest `serial-sized` partition
         * for the wanted element with an another recursive attempt:
         */
        if (serialSizeOfTheElementToLookFor < lowPartitionSize) {
            return selectTheIthElementInItsSize_UnSecured(
                    array, lowestIndexToSearchAt, pivotIndex - 1,
                    serialSizeOfTheElementToLookFor);
        } else {
            return selectTheIthElementInItsSize_UnSecured(
                    array, pivotIndex + 1, highestIndexToSearchAt,
                    serialSizeOfTheElementToLookFor - lowPartitionSize);
        }
    }

    template<class T>
    static T getMiddleElementInASortedArray(T *array, int size) {
        return array[(size - 1) / 2];
    }

  public:
    /**
     * @brief sorts an array using the `quick-sort` algorithm.
     *
     * @note This method is **secured**.
     * @tparam T element of the array.
     * @param array the array to be sorted.
     * @param size the size of the given @p array.
     * @see quickSortRecursive(T *, int, int)
     * @see partition(T *, int, int, int)
     */
    template<typename T> static void quickSort(T *array, int size) {
        quickSortRecursive(array, 0, size - 1);
    }

  private:
    /**
     * @brief sorts an array using the `quick-sort` algorithm.
     *
     * This done by using the @link partition(T *, int, int, int) @endlink
     * method, with the `pivot` index being the `first` index possible.
     * @warning this method doesn't check that the
     *          @p lowestIndexPossible and @p highestIndexPossible
     *          are valid indexes in the array.
     * @tparam T element of the array.
     * @param array the array to be sorted.
     * @param lowestIndexPossible the lowest index in the @p array given.
     * @param highestIndexPossible the highest index in the @p array given.
     * @see partition(T *, int, int, int)
     */
    template<typename T>
    static void quickSortRecursive(T *array, int lowestIndexPossible,
                                   int highestIndexPossible) {
        if (lowestIndexPossible < highestIndexPossible) {
            int pivot =
                    partition(array, lowestIndexPossible,
                              highestIndexPossible); // pivot the `first` index.
            quickSortRecursive(array, lowestIndexPossible, pivot - 1);
            quickSortRecursive(array, pivot + 1, highestIndexPossible);
        }
    }

  private:
    /**
     * @brief This method divides a given @p array to @p k smaller arrays,
     *        and invokes the @p forEachSmallArrayFunction function for
     *        each of the divided smaller arrays.
     * @note The method divides the given @p array such that the sizes of the
     *       smaller arrays are spread as equally as possible.
     * @tparam T the `type` of elements in the array given.
     * @param array the array to divide to @p k smaller arrays.
     * @param size the size of the @p array given.
     * @param k the division parameter.
     * @param forEachSmallArrayFunction this function is being invoked
     *                                  `for-each` smaller array.
     */
    template<typename T>
    static void divideArrayToKSmallerArrays(
            T *array, int size, int k,
            const std::function<void(T *, int)> &forEachSmallArrayFunction) {

        /*
         * Save here the size of the last small array.
         * Attention: must initialize with `0`.
         */
        int lastSmallArraySize = 0;
        while ((size > 0) && (k > 0)) {
            int *currSmallArray     = array + lastSmallArraySize;
            int  currSmallArraySize = ceil((double) size / k);

            /* Do something to the current small array. */
            forEachSmallArrayFunction(currSmallArray, currSmallArraySize);

            /* Step ahead. */
            size = size - currSmallArraySize;
            k--;
            lastSmallArraySize = currSmallArraySize;
        }
    }
};

#endif //MIVNEI_NETUNIM_EX2_MY_ALGORITHMS_H
