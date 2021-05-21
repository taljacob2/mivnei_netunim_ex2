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
        divideArrayToKSmallerArrays<K, int>(
                *array, size, k, smallArrayLocations, smallArraySizes,
                my_algorithms::quickSort<K>, minHeap);

        deleteMinAndCheckFromWhichSmallArray(size, smallArrayLocations,
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
     * @tparam T the `type` of elements in the array given.
     * @param array the array to divide to @p k smaller arrays.
     * @param size the size of the @p array given.
     * @param k the division parameter.
     * @param forEachSmallArrayFunction this function is being invoked
     *                                  `for-each` smaller array.
     */
    template<typename K, typename V>
    static void divideArrayToKSmallerArrays(
            K *array, int size, int k, K **smallArrayLocations,
            int *                                smallArraySizes,
            const std::function<void(K *, int)> &forEachSmallArrayFunction,
            MinHeap<K, V> &                      minHeap) {

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
            auto *entryToInsert = new Entry<K, V>(currSmallArray[0], kIndex);
            minHeap.insert(entryToInsert);

            /* Step ahead. */
            size = size - currSmallArraySize;
            currK--;
            lastSmallArraySize = currSmallArraySize;
        }
    }

    template<typename K, typename V>
    static void deleteMinAndCheckFromWhichSmallArray(int size,
                                                     K **smallArrayLocations,
                                                     K * smallArraySizes,
                                                     MinHeap<K, V> &minHeap,
                                                     K *resultArray) {
        for (int i = 0; i < size; i++) {

            // TODO: checking print of HEAP:
            std::cout << minHeap << "\n";

            /* Delete the minimal element from the heap. */
            Entry<K, V> *deletedElement = minHeap.deleteMin();

            /* Insert minimal `key` to `resultArray`. */
            resultArray[i] = deletedElement->getKey();

            /* If there are elements in the according array. */
            if ((smallArraySizes[deletedElement->getValue()]) > 0) {

                /* Step ahead the `location` of the according small array. */
                smallArrayLocations[deletedElement->getValue()]++;

                /* Decrease the `size` of the according small array by `1`. */
                smallArraySizes[deletedElement->getValue()]--;

                /*
                 * `Insert` the next smaller element in the according small array
                 * to the given `Minimum-Heap`.
                 * (= the `first` element in the small array).
                 */
                auto *elementToInsert = new Entry<K, V>(
                        (smallArrayLocations[deletedElement->getValue()])[0],
                        deletedElement->getValue());

                minHeap.insert(elementToInsert);
            } else {

                /*
                 * Should not be happening if the `smallArraySizes` is
                 * properly made.
                 */
                // TODO: change to `wrong input`
                throw std::runtime_error("You have tried to remove an "
                                         "element from a `small array` that "
                                         "is already empty.");
            }
        }
    }
};

#endif //MIVNEI_NETUNIM_EX1_ALGORITHMSANDMINHEAP_H
