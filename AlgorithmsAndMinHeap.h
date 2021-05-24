//
// Created by Tal on 21-May-21.
//

#ifndef MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H
#define MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H

#include "MinHeap.h"

/**
 * @brief This class bundles all the methods that require to `include` the
 *        `algorithm` methods in the program, and the `MinHeap` class together.
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
     *      @li (K *) smallArrayLocations - is an array that stores the
     *      `starting` location of each `small array`.
     *      @li (K **) changeableSmallArrayLocations - is the same as
     *      `smallArrayLocations`, but on each `remove` of a `first` element in
     *      a `small array`, set the location of the according `small array`
     *      to be `1` location ahead.
     *      @li (long int *) smallArraySizes - is an array that stores the `size` of
     *      each `small array`.
     * The method creates a `MinHeap`:
     *      This `MinHeap`'s elements are pointers to `Entries` such that
     *      each `Entry` is composed of a `key` and a `value.
     *      Its `key`, stands for the smallest element in each `small array` -
     *      and its `value` stands for an *long int* number that determines the
     *      specific `small array` from which that element came from.
     *
     * @note in case @p k is smaller than the @p size of the @p array given,
     *       then the method invokes @link my_algorithms::quickSort(K *, long int)
     *       @endlink.
     * @note in case @p k is less than `2`, then the method invokes @link
     *       my_algorithms::quickSort(K *, long int) @endlink.
     * @note In case @p k equals to `2`, this algorithm is actually the known
     *       `MergeSort` algorithm.
     * @tparam K the `type` of the elements in the @p array given.
     * @param array the array to sort. *Must* be dynamically allocated.
     * @param size the size of the @p array to sort.
     * @param k the *division* parameter, when sorting the array.
     * @see my_algorithms::quickSort(K *, long int)
     * @see MinHeap
     * @see Entry
     */
    template<typename K>
    static void kWayMergeSort(K *array, const unsigned long int size,
                              unsigned long int k) {
        if ((size < k) || (k == 0) || (k == 1)) {
            my_algorithms::quickSort(array, size);
            return;
        }

        K **      smallArrayLocations           = new K *[k];
        K **      changeableSmallArrayLocations = new K *[k];
        long int *smallArraySizes               = new long int[k];

        MinHeap<K, long int> minHeap(k);

        /*
         * Divide the array to K `smaller arrays`.
         * For each `small array`: - Sort the array.
         *                         - `insert` the `first` element in the array to
         *                           the `Minimum-Heap` provided.
         */
        divideArrayToKSmallerArrays<K>(array, size, k, smallArrayLocations,
                                       changeableSmallArrayLocations,
                                       smallArraySizes, kWayMergeSort<K>,
                                       minHeap);

        deleteMinAndCheckFromWhichSmallArray<K>(array, size,
                                                changeableSmallArrayLocations,
                                                smallArraySizes, minHeap);

        /* Delete each `small array`. */
        for (unsigned long int i = 0; i < k; i++) {
            delete[] smallArrayLocations[i];
        }
        delete[] smallArrayLocations;
        delete[] changeableSmallArrayLocations;
        delete[] smallArraySizes;
    }

  private:
    /**
     * @brief This method divides a given @p array to @p k `smaller arrays`,
     *        and invokes the @p forEachSmallArrayFunction function for
     *        each of the divided `smaller arrays`.
     *
     * @attention this method creates @p k `small arrays` that their
     *            `starting` location is stored in the @p smallArrayLocations array.
     *            So, after the use of this method, the user *must* `delete` each
     *            `small array` with a loop:
     *            @code
     *            // Delete each `small array`.
     *            for (long int i = 0; i < k; i++) { delete[] smallArrayLocations[i]; }
     *            @endcode
     *
     * @note The method divides the given @p array such that the sizes of the
     *       `smaller arrays` are spread as equally as possible.
     * @tparam K the `type` of elements in the array given.
     *           this would serve as the `key` type of the elements.
     * @param array the array to divide to @p k `smaller arrays`.
     * @param size the size of the @p array given.
     * @param k the division parameter.
     * @param smallArrayLocations is an array that stores the
     *                            `starting` location of each `small array`.
     * @param changeableSmallArrayLocations is the same as
     *                                      `smallArrayLocations`, but on each
     *                                      `remove` of a `first` element in
     *                                      a `small array`, set the location
     *                                      of the according `small array`
     *                                      to be `1` location ahead.
     * @param smallArraySizes is an array that stores the `size` of each
     *                        `small array`.
     * @param forEachSmallArrayFunction this function is being invoked
     *                                  `for-each` `small array`.
     * @param minHeap is the *Minimum-Heap* that has been pre-initialized to the
     *                `physicalSize` of @p k. And in this method, on each
     *                iteration, right after the @p
     *                forEachSmallArrayFunction is being invoked, this
     *                *Minimum-Heap* is `inserting` the `first` element in
     *                each `small array` to it.
     * @see MinHeap
     */
    template<typename K>
    static void divideArrayToKSmallerArrays(
            K *array, unsigned long int size, unsigned long int k,
            K **smallArrayLocations, K **changeableSmallArrayLocations,
            long int *smallArraySizes,
            const std::function<void(K *, const unsigned long int,
                                     unsigned long int)>
                    &             forEachSmallArrayFunction,
            MinHeap<K, long int> &minHeap) {

        /*
         * Save here the size of the last `small array`.
         * Attention: must initialize with `0`.
         */
        long int lastSmallArraySize = 0;
        long int currK              = k;
        while ((size > 0) && (currK > 0)) {

            /* Determines the current iteration. */
            long int kIndex = k - currK;

            /* Get `currSmallArrayStartLocation` `size`. */
            long int currSmallArraySize =
                    ceil(static_cast<double>(size) / currK);

            /*
             * Insert the `currSmallArrayStartLocation` `size` to the
             * `smallArraySizes` array.
             */
            smallArraySizes[kIndex] = currSmallArraySize;

            /* Get `currSmallArrayStartLocation` `location`. */
            K *currSmallArrayStartLocation = array + lastSmallArraySize;

            /* Copy the correct amount of elements to a `small array`. */
            K *currSmallArrayLocation = my_algorithms::copyArray(
                    currSmallArrayStartLocation, currSmallArraySize);

            /*
             * Insert the `currSmallArrayStartLocation` to the
             * `smallArrayLocations` and `changeableSmallArrayLocations` arrays.
             */
            smallArrayLocations[kIndex]           = currSmallArrayLocation;
            changeableSmallArrayLocations[kIndex] = currSmallArrayLocation;

            /* Do something to the current small array. */
            forEachSmallArrayFunction(currSmallArrayLocation,
                                      currSmallArraySize, k);

            /*
             * Take the `first` element in the current small array,
             * and `insert` it to the `Minimum-Heap` as a `key` of an `Entry`,
             * and set this `Entry`'s `value` to be the
             * `currSmallArrayStartLocation` iteration index.
             * Attention: `Entry` must be `lvalue`.
             */
            auto *entryToInsert =
                    new Entry<K, long int>(currSmallArrayLocation[0], kIndex);
            minHeap.insert(entryToInsert);
            stepAheadSmallArray(changeableSmallArrayLocations, smallArraySizes,
                                entryToInsert);

            /* Step ahead. */
            size = size - currSmallArraySize;
            currK--;
            lastSmallArraySize += currSmallArraySize;
        }
    }

    /**
     * @brief This method, for @p size times, deletes the `smallest` element
     *        in the @p minHeap, and inserts it to the @p array. Then, takes the
     *        next `smallest` element from the according `small array` that
     *        this `deletedElement` came from, and inserts it to the @p minHeap.
     *        At the end of this method, the @p array would be sorted.
     *
     * @tparam K the `type` of elements in the array given.
                 this would serve as the `key` type of the elements.
     * @param array the array to be sorted. The array to has been divided to `k`
     *              `smaller arrays`.
     * @param size the size of the @p array given.
     * @param changeableSmallArrayLocations is the same as
     *                                      `smallArrayLocations`, but on each
     *                                      `remove` of a `first` element in
     *                                      a `small array`, set the location
     *                                      of the according `small array`
     *                                      to be `1` location ahead.
     * @param smallArraySizes is an array that stores the `size` of each
     *                        `small array`.
     * @param minHeap is the *Minimum-Heap* that has been pre-initialized to the
     *                `physicalSize` of `k`. And stores the all the `first`
     *                elements in each `small array`. Means, it stores all
     *                the `smallest` `k` elements in the original @p array.
     * @see MinHeap
     */
    template<typename K>
    static void deleteMinAndCheckFromWhichSmallArray(
            K *array, unsigned long int size, K **changeableSmallArrayLocations,
            long int *smallArraySizes, MinHeap<K, long int> &minHeap) {
        for (unsigned long int i = 0; i < size; i++) {

            /* Remove the minimal element from the heap. */
            Entry<K, long int> *deletedElement = minHeap.deleteMin();

            /* Insert minimal `key` to `resultArray`. */
            array[i] = deletedElement->getKey();

            /* If there are elements in the according array. */
            if ((smallArraySizes[deletedElement->getValue()]) > 0) {

                /*
                 * `Insert` the next smaller element in the according small array
                 * to the given `Minimum-Heap`.
                 * (= the `first` element in the small array).
                 */
                auto *elementToInsert = new Entry<K, long int>(
                        (changeableSmallArrayLocations
                                 [deletedElement->getValue()])[0],
                        deletedElement->getValue());
                minHeap.insert(elementToInsert);
                stepAheadSmallArray(changeableSmallArrayLocations,
                                    smallArraySizes, deletedElement);
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
     * @param changeableSmallArrayLocations the array that stores the
     *                                      current starting `locations` of
     *                                      all the `small-arrays`.
     * @param smallArraySizes the array that stores the `sizes` of all
     *                        the `small-arrays`.
     * @param deletedElement the element that has been removed from a
     *                       generic `small-array`.
     */
    template<typename K>
    static void stepAheadSmallArray(K **      changeableSmallArrayLocations,
                                    long int *smallArraySizes,
                                    Entry<K, long int> *deletedElement) {

        /*
         * Step ahead the `location` of the according small array,
         * to point to the next `smallest` element in the array.
         */
        changeableSmallArrayLocations[deletedElement->getValue()]++;

        /* Decrease the `size` of the according small array by `1`. */
        smallArraySizes[deletedElement->getValue()]--;
    }
};

#endif //MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H
