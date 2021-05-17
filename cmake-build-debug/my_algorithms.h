//
// Created by Tal on 27-Mar-21.
//

#ifndef MIVNEI_NETUNIM_EX1_MY_ALGORITHMS_H
#define MIVNEI_NETUNIM_EX1_MY_ALGORITHMS_H

/**
 * @brief this class bundles together all the algorithm
 *        methods of the program.
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
class my_algorithms {
public:

    /**
     * @brief generic algorithm to copy an array.
     *
     * @returns the `new` copied array.
     */
    template<class T>
    static T *copyArray(const T *array, int size) {
        auto *copiedArr = new T[size];
        for (int i = 0; i < size; ++i) {
            copiedArr[i] = array[i];
        }
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
    template<class T>
    static void swap(T *array, int index1, int index2) {
        T tmp = array[index1];
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
    template<class T>
    static void swap(T &element1, T &element2) {
        T tmp = element1;
        element1 = element2;
        element2 = tmp;
    }

    /**
     * @brief sorts the array given array.
     *
     * @param array
     * @param size the size of the array.
     */
    template<class T>
    static void sort_insertion(T *array,
                               int size) {
        if (size <= 1) {
            return;
        }

        for (int head_index = 1; head_index < size; ++head_index) {
            int curr_head_index = head_index;
            for (int predecessor_index = head_index - 1;
                 predecessor_index >= 0; predecessor_index--) {
                if ((array)[predecessor_index] > (array)[curr_head_index]) {
                    swap<T>((array), curr_head_index, predecessor_index);
                    curr_head_index = predecessor_index;
                } else { break; }
            }
        }
    }

    /**
     * @brief this method is made for getting the
     *        `sort_insertion_` method name by reflection.
     *
     * @param outputParameterForThisFunctionName output parameter
     *                                           to get this function's name.
     * @see sort_insertion (T *, int)
     */
    template<class T>
    static void sort_insertion_(T *array,
                                int size,
                                char *&outputParameterForThisFunctionName) {

        // get this function's name:
        outputParameterForThisFunctionName = const_cast<char *>(__func__);
        sort_insertion(array, size);
    }

    /**
     * @brief sorts a specific element in the array, named as `pivot`,
     *        and returns its index.
     *
     * @warning this method doesn't check that the
     *          @p lowestIndex and @p highestIndex
     *          are valid indexes in the array.
     * @note this method places the `pivot` in the **earliest** index possible.
     * @tparam T element of the array.
     * @param array the array to be sorted.
     * @param lowestIndexPossible the lowest index in the @p array given.
     * @param highestIndexPossible the highest index in the @p array given.
     * @param indexOfElementToServeAsPivot it is possible to insert here the
     *                                     desired `index` for the `pivot`
     *                                     to be found.
     * @returns the pivot's index.
     * @see swap(T *, int, int) - for swapping the elements in the array.
     * @see swap(T &, T &) - for swapping the elements' indexes in the array.
     */
    template<class T>
    static int
    partition(T *array, int lowestIndexPossible, int highestIndexPossible,
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
                } else { --nonPivotIndex; }
            } else if (nonPivotIndex < pivotIndex) {
                if (array[nonPivotIndex] > array[pivotIndex]) {
                    swap<T>(array, pivotIndex, nonPivotIndex);
                    swap<int>(pivotIndex, nonPivotIndex);
                    --nonPivotIndex;
                } else { ++nonPivotIndex; }
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
     * @see  selectTheIthElementInItsSize_UnSecured(T *, int, int, int)
     */
    template<class T>
    static T
    selection_TheIthElementInItsSize(T *array, int size,
                                     int serialSizeOfTheElementToLookFor) {
        return selectTheIthElementInItsSize_UnSecured(array, 0, size - 1,
                                                      serialSizeOfTheElementToLookFor);
    }

    /**
     * @brief this method is made for getting the
     *        `selectTheIthElementInItsSize_` method name by reflection.
     *
     * @param outputParameterForThisFunctionName output parameter
     *                                           to get this function's name.
     * @see selection_TheIthElementInItsSize (T *, int, int)
     */
    template<class T>
    static T
    selection_TheIthElementInItsSize_(T *array, int size,
                                      int serialSizeOfTheElementToLookFor,
                                      char *&outputParameterForThisFunctionName) {

        // get this function's name:
        outputParameterForThisFunctionName = const_cast<char *>(__func__);
        return selection_TheIthElementInItsSize(array, size,
                                                serialSizeOfTheElementToLookFor);
    }

    /**
     * @brief sorts an array using the `bubble-sort` algorithm.
     *
     * @tparam T element of the array.
     * @param array the array to be sorted.
     * @param size the size of the given @p array.
     */
    template<class T>
    static void bubbleSort(T *array, int size) {
        for (int i = 0; i < size; ++i) {
            for (int j = size - 1; j > i; --j) {
                if (array[i] > array[j]) {
                    swap(array, i, j);
                }
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
            int divisionCounter = 1;
            int lastDividedArraySize = DIVISION;
            int divisionInteger = 1;
            whileOfBubbleSort_division_TheIthElementInItsSize<T, DIVISION>(
                    array, size,
                    divisionCounter,
                    divisionInteger,
                    lastDividedArraySize);
            T *takenMiddlesArray = new T[divisionCounter];
            getMiddleArray_division_TheIthElementInItsSize<T, DIVISION>(array,
                                                                        takenMiddlesArray,
                                                                        divisionCounter,
                                                                        lastDividedArraySize);
            int k_index;
            try {
                getTakenMiddlesArrayPivotElementAndIndex_division_TheIthElementInItsSize<
                        T, DIVISION>(
                        array,
                        size, takenMiddlesArray,
                        divisionCounter,
                        k_index);
            } catch (std::exception &e) {
                return 0;
            }
            delete[] takenMiddlesArray;
            return returnOf_division_TheIthElementInItsSize<T, DIVISION>(array,
                                                                         size,
                                                                         serialSizeOfTheElementToLookFor,
                                                                         k_index);
        }
    }

    /**
     * implements `quintuplet_TheIthElementInItsSize` as @e DIVISION = 5.
     * @see quintuplet_TheIthElementInItsSize (T *, int, int)
     */
    template<class T>
    static T
    quintuplet_TheIthElementInItsSize(T *array, int size,
                                      int serialSizeOfTheElementToLookFor) {
        return division_TheIthElementInItsSize<T, 5>(array, size,
                                                     serialSizeOfTheElementToLookFor);
    }

    /**
     * @brief this method is made for getting the
     *        `sort_quintuplet_` method name by reflection.
     *
     * @param outputParameterForThisFunctionName output parameter
     *                                           to get this function's name.
     * @see quintuplet_TheIthElementInItsSize (T *, int, int)
     */
    template<class T>
    static T
    quintuplet_TheIthElementInItsSize_(T *array, int size,
                                       int serialSizeOfTheElementToLookFor,
                                       char *&outputParameterForThisFunctionName) {

        // get this function's name:
        outputParameterForThisFunctionName = const_cast<char *>(__func__);
        return quintuplet_TheIthElementInItsSize<T>(array, size,
                                                    serialSizeOfTheElementToLookFor);
    }

private:

    template<class T, int DIVISION>
    static void
    whileOfBubbleSort_division_TheIthElementInItsSize(T *array, int size,
                                                      int &divisionCounter,
                                                      int &divisionInteger,
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
    static void getMiddleArray_division_TheIthElementInItsSize(T *array,
                                                               T *takenMiddlesArray,
                                                               int divisionCounter,
                                                               int lastDividedArraySize) {
        int i = 0;
        for (; i < divisionCounter - 1; ++i) {

            /*
             * get middleElement in each divided-array,
             * and insert it to `takenMiddlesArray`:
             */
            takenMiddlesArray[i] =
                    getMiddleElementInASortedArray(
                            array + (i * DIVISION),
                            DIVISION);
        }

        // get middleElement from the last leftOver array (special case):
        takenMiddlesArray[i] =
                getMiddleElementInASortedArray(
                        array + (i * DIVISION),
                        lastDividedArraySize);
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
                division_TheIthElementInItsSize<T, DIVISION>(takenMiddlesArray,
                                                             divisionCounter,
                                                             ((divisionCounter -
                                                               1) / 2) + 1);

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
    static T returnOf_division_TheIthElementInItsSize(T *array, int size,
                                                      int i,
                                                      int k_index) {
        int i_index = i - 1;

        if (i_index < k_index) {
            return division_TheIthElementInItsSize<T, DIVISION>(array, k_index,
                                                                i);
        } else if (k_index < i_index) {
            return division_TheIthElementInItsSize<T, DIVISION>(
                    array + (k_index + 1),
                    size - (k_index + 1),
                    (i_index - k_index));
        } else if (i_index == k_index) {
            return array[k_index]; // return the value of the i'th element in its size.
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
     * @see partition(T *, int, int)
     * @see selectTheIthElementInItsSize(T *, int, int)
     */
    template<class T>
    static T
    selectTheIthElementInItsSize_UnSecured(T *array, int lowestIndexToSearchAt,
                                           int highestIndexToSearchAt,
                                           int serialSizeOfTheElementToLookFor) {

        // get a pivotIndex:
        int pivotIndex = partition(array, lowestIndexToSearchAt,
                                   highestIndexToSearchAt);

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
            return selectTheIthElementInItsSize_UnSecured(array,
                                                          lowestIndexToSearchAt,
                                                          pivotIndex - 1,
                                                          serialSizeOfTheElementToLookFor);
        } else {
            return selectTheIthElementInItsSize_UnSecured(array, pivotIndex + 1,
                                                          highestIndexToSearchAt,
                                                          serialSizeOfTheElementToLookFor -
                                                          lowPartitionSize);
        }
    }

    template<class T>
    static T getMiddleElementInASortedArray(T *array, int size) {
        return array[(size - 1) / 2];
    }
};

#endif //MIVNEI_NETUNIM_EX1_MY_ALGORITHMS_H
