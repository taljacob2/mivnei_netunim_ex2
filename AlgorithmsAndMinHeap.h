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
    template<typename K> static void kWayMergeSort(K *array, int size, int k) {
        if (size < k) {
            quickSort(array, size);
            return;
        }
        /* XXX Note: (int)`VALUE` = (kGiven - currK) */
        MinHeap<K, int> minHeap;

        // FIXME: change `quickSort` to `recursive` call !!!! -->>>
        divideArrayToKSmallerArrays<K, int>(array, size, k,
                                            my_algorithms::quickSort, minHeap);
    }

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
    template<typename K, typename V>
    static void divideArrayToKSmallerArrays(
            K *array, int size, int k,
            const std::function<void(K *, int)> &forEachSmallArrayFunction,
            MinHeap<K, V> &                      minHeap) {

        /*
         * Save here the size of the last small array.
         * Note: must initialize with `0`.
         */
        int lastSmallArraySize = 0;
        int currK              = k;
        while ((size > 0) && (currK > 0)) {
            int currSmallArraySize = ceil((double) size / k);

            /* Do something to the current small array. */
            forEachSmallArrayFunction(array + lastSmallArraySize,
                                      currSmallArraySize);

            /*
             * Take the first element in the smaller array, and `insert` it to
             * the `Minimum-Heap`.
             */

            // NOTE: `Entry` must be `lvalue`.
            auto *entryToInsert =
                    new Entry((array + lastSmallArraySize)[0], k - currK);
            minHeap.insert(entryToInsert);

            /* Step ahead. */
            size = size - currSmallArraySize;
            currK--;
            lastSmallArraySize = currSmallArraySize;
        }
    }
};

#endif //MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H
