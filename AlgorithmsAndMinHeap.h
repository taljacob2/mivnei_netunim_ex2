//
// Created by Tal on 21-May-21.
//

#ifndef MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H
#define MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H

#include "MinHeap.h"

/**
 * This class bundles all the methods that require to `include` the
 * `algorithm` methods in the program, and the `MinHeap` class together.
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 * @see my_algorithms
 * @see MinHeap
 */
class AlgorithmsAndMinHeap {
  public:
    /**
     * @brief This algorithm sorts the @p array given, by dividing it to @p k
     *        `smaller arrays`.
     *        Then for each `small array`:
     *          @li Sort the array.
     *          @li `insert` the `first` element in the array to the `Minimum-Heap`
     *          provided.
     *
     *        Then, for `size` number of times:
     *          @li Invoke the `MinHeap.deleteMin()` method to get the `smallest`
     *          element in the MinHeap, and insert it to the `resultArray`.
     *          @li Determine the specific `small array` from which that element
     *          came from, and extract another the next `smallest` element in
     *          it to the `MinHeap`, instead of the removed element.
     *
     * The method handles 3 arrays:
     *      @li (K *) resultArray - is the result array.
     *      @li (K **) resultArray - is an array that stores the start
     *      `location` of each `small array`.
     *      @li (int *) smallArraySizes - is an array that stores the `size` of
     *      each `small array`.
     * The method creates a `MinHeap`:
     *      This `MinHeap`'s elements are pointers to `Entries` such that
     *      each `Entry` is composed of a `key` and a `value.
     *      Its `key`, stands for the smallest element in each `small array` -
     *      and its `value` stands for an *int* number that determines the
     *      specific `small array` from which that element came from.
     *
     * @note in case @p k is smaller than the @p size of the @p array given,
     *       then the method invokes @link my_algorithms::quickSort(K *, int)
     *       @endlink.
     * @note In case @p k equals to `2`, this algorithm is actually the known
     *       `MergeSort` algorithm.
     * @attention the @p array given *must* be dynamically allocated.
     * @tparam K the `type` of the elements in the @p array given.
     * @param array the array to sort. *Must* be dynamically allocated.
     * @param size the size of the @p array to sort.
     * @param k the *division* parameter, when sorting the array.
     * @see my_algorithms::quickSort(K *, int)
     * @see MinHeap
     * @see Entry
     */
    template<typename K> static void kWayMergeSort(K **array, int size, int k) {
        if (size < k) {
            my_algorithms::quickSort(*array, size);
            return;
        }

        K *  resultArray         = new K[size];
        K ** smallArrayLocations = new K *[k];
        int *smallArraySizes     = new int[k];

        MinHeap<K, int> minHeap(k);

        /*
         * Divide the array to K `smaller arrays`.
         * For each `small array`: - Sort the array.
         *                         - `insert` the `first` element in the array to
         *                           the `Minimum-Heap` provided.
         */
        // FIXME: change `quickSort` to `recursive` call !!!! -->>>
        divideArrayToKSmallerArrays<K>(*array, size, k, smallArrayLocations,
                                       smallArraySizes,
                                       my_algorithms::quickSort<K>, minHeap);

        deleteMinAndCheckFromWhichSmallArray<K>(size, smallArrayLocations,
                                                smallArraySizes, minHeap,
                                                resultArray);

        delete[] * array;
        *array = resultArray;

        delete[] smallArrayLocations;
        delete[] smallArraySizes;
    }

  private:
    /**
     * @brief This method divides a given @p array to @p k `smaller arrays`,
     *        and invokes the @p forEachSmallArrayFunction function for
     *        each of the divided `smaller arrays`.
     * @note The method divides the given @p array such that the sizes of the
     *       `smaller arrays` are spread as equally as possible.
     * @tparam K the `type` of elements in the array given.
     *           this would serve as the `key` type of the elements.
     * @param array the array to divide to @p k `smaller arrays`.
     * @param size the size of the @p array given.
     * @param k the division parameter.
     * @param forEachSmallArrayFunction this function is being invoked
     *                                  `for-each` smaller array.
     */
    template<typename K>
    static void divideArrayToKSmallerArrays(
            K *array, int size, int k, K **smallArrayLocations,
            int *                                smallArraySizes,
            const std::function<void(K *, int)> &forEachSmallArrayFunction,
            MinHeap<K, int> &                    minHeap) {

        /*
         * Save here the size of the last `small array`.
         * Attention: must initialize with `0`.
         */
        int lastSmallArraySize = 0;
        int currK              = k;
        while ((size > 0) && (currK > 0)) {

            /* Determines the current iteration. */
            int kIndex = k - currK;

            /* Get `currSmallArray` `location`. */
            int *currSmallArray = array + lastSmallArraySize;

            /*
             * Insert the `currSmallArray` `location` to the
             * `smallArrayLocations` array.
             */
            smallArrayLocations[kIndex] = currSmallArray;

            /* Get `currSmallArray` `size`. */
            int currSmallArraySize = ceil((double) size / currK);

            /*
             * Insert the `currSmallArray` `size` to the
             * `smallArraySizes` array.
             */
            smallArraySizes[kIndex] = currSmallArraySize;


            /* Do something to the current small array. */
            forEachSmallArrayFunction(currSmallArray, currSmallArraySize);

            /*
             * Take the `first` element in the current small array,
             * and `insert` it to the `Minimum-Heap` as a `Key` of an `Entry`,
             * and set this `Entry`'s `Value` to be the `currSmallArray`
             * iteration index.
             * Attention: `Entry` must be `lvalue`.
             */
            auto *entryToInsert = new Entry<K, int>(currSmallArray[0], kIndex);
            minHeap.insert(entryToInsert);
            stepAheadSmallArray(smallArrayLocations, smallArraySizes,
                                entryToInsert);

            /* Step ahead. */
            size = size - currSmallArraySize;
            currK--;
            lastSmallArraySize += currSmallArraySize;
        }
    }

    template<typename K>
    static void deleteMinAndCheckFromWhichSmallArray(int  size,
                                                     K ** smallArrayLocations,
                                                     int *smallArraySizes,
                                                     MinHeap<K, int> &minHeap,
                                                     K *resultArray) {
        for (int i = 0; i < size; i++) {

            /* Remove the minimal element from the heap. */
            Entry<K, int> *deletedElement = minHeap.deleteMin();

            /* Insert minimal `key` to `resultArray`. */
            resultArray[i] = deletedElement->getKey();

            /* If there are elements in the according array. */
            if ((smallArraySizes[deletedElement->getValue()]) > 0) {

                /*
                 * `Insert` the next smaller element in the according small array
                 * to the given `Minimum-Heap`.
                 * (= the `first` element in the small array).
                 */
                auto *elementToInsert = new Entry<K, int>(
                        (smallArrayLocations[deletedElement->getValue()])[0],
                        deletedElement->getValue());
                minHeap.insert(elementToInsert);
                stepAheadSmallArray(smallArrayLocations, smallArraySizes,
                                    deletedElement);
            }

            /* Delete the element from memory. */
            delete deletedElement;
        }
    }

    /**
     * @brief This *private* method is invoked only when we have removed an
     *        element from a `small-array`. The method ensures to
     *        `step-ahead` the `location` of the according `small-array`
     *        location, and to decrease by `1` the `size` of the according
     *        `small-array` size.
     *
     * @warning this method does not check that the
     *          `smallArraySizes[deletedElement->getValue()]` is a number greater
     *          than `0`. Thus, you must use this method in a parentheses of:
     *          @code
     *          if ((smallArraySizes[deletedElement->getValue()]) > 0) {
     *               // call this method...
     *          }
     *          @endcode
     * @tparam K the `key` of the element.
     * @param smallArrayLocations the array that stores the starting
     *                            `locations` of all the `small-arrays`.
     * @param smallArraySizes the array that stores the `sizes` of all
     *                        the `small-arrays`.
     * @param deletedElement the element that has been removed from a
     *                       generic `small-array`.
     */
    template<typename K>
    static void stepAheadSmallArray(K **           smallArrayLocations,
                                    int *          smallArraySizes,
                                    Entry<K, int> *deletedElement) {

        /* Step ahead the `location` of the according small array. */
        smallArrayLocations[deletedElement->getValue()]++;

        /* Decrease the `size` of the according small array by `1`. */
        smallArraySizes[deletedElement->getValue()]--;
    }
};

#endif //MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H
