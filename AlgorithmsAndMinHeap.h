//
// Created by Tal on 21-May-21.
//

#ifndef MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H
#define MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H

#include "MinHeap.h"
class AlgorithmsAndMinHeap {
  public:
    /**
     * @brief This algorithm sorts the @p array given, by dividing it to @p k
     *        smaller arrays. Sorting each of them. And finally *merging* them
     *        together.
     *
     * @note in case @p k is smaller than the @p size of the @p array given,
     *       then the method invokes @link my_algorithms::quickSort(K *, int) @endlink.
     * @note In case @p k equals to `2`, this algorithm is actually the known
     *       `MergeSort` algorithm.
     * @tparam K the `type` of the elements in the @p array given.
     * @param array the array to sort.
     * @param size the size of the @p array to sort.
     * @param k the *division* parameter, when sorting the array.
     * @see my_algorithms::quickSort(K *, int)
     */
    template<typename K> static void kWayMergeSort(K **array, int size, int k) {
        if (size < k) {
            my_algorithms::quickSort(*array, size);
            return;
        }

        K *  resultArray         = new K[size];
        K ** smallArrayLocations = new K *[k];
        int *smallArraySizes     = new int[k];


        /* XXX Note: (int)`VALUE` = (kGiven - currK) */
        MinHeap<K, int> minHeap(k);

        /*
         * Divide the array to K smaller arrays.
         * For each small array: - Sort the array.
         *                       - `insert` the `first` element in the array to
         *                         the `Minimum-Heap` provided.
         */
        // FIXME: change `quickSort` to `recursive` call !!!! -->>>
        divideArrayToKSmallerArrays<K>(*array, size, k, smallArrayLocations,
                                       smallArraySizes,
                                       my_algorithms::quickSort<K>, minHeap);

        deleteMinAndCheckFromWhichSmallArray<K>(size, smallArrayLocations,
                                                smallArraySizes, minHeap,
                                                resultArray);

        *array = my_algorithms::copyArray(resultArray, size);

        delete[] smallArrayLocations;
        delete[] smallArraySizes;
        delete[] resultArray;
    }

  private:
    /**
     * @brief This method divides a given @p array to @p k smaller arrays,
     *        and invokes the @p forEachSmallArrayFunction function for
     *        each of the divided smaller arrays.
     * @note The method divides the given @p array such that the sizes of the
     *       smaller arrays are spread as equally as possible.
     * @tparam K the `type` of elements in the array given.
     *           this would serve as the `key` type of the elements.
     * @param array the array to divide to @p k smaller arrays.
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
         * Save here the size of the last small array.
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
            int currSmallArraySize = ceil((double) size / k);

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

            // BUG: checking print of HEAP:
            std::cout << minHeap << "\n";

            /* Delete the minimal element from the heap. */
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
        }
    }

    /**
     * @brief This *private* method is invoked only when we have removed an
     *        element from a `small-array`. The method ensures to
     *        `step-ahead` the `location` of the according `small-array`
     *        location, and to decrease the `size` of the according
     *        `small-array` size.
     *
     * @warning this method does not check that the
     *          `smallArraySizes[@p deletedElement->getValue()]` is a number greater
     *          than `0`. Thus, you must use this method in a parentheses of:
     *          @code
     *          if ((smallArraySizes[@p deletedElement->getValue()]) > 0) {
     *               // call this method...
     *          }
     *          @endcode
     * @tparam K
     * @tparam V
     * @param smallArrayLocations
     * @param smallArraySizes
     * @param deletedElement
     */
    template<typename K, typename V>
    static void stepAheadSmallArray(K **         smallArrayLocations,
                                    int *        smallArraySizes,
                                    Entry<K, V> *deletedElement) {

        /* Step ahead the `location` of the according small array. */
        smallArrayLocations[deletedElement->getValue()]++;

        /* Decrease the `size` of the according small array by `1`. */
        smallArraySizes[deletedElement->getValue()]--;
    }
};

#endif //MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H
