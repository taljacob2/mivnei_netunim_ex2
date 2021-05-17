//
// Created by Tal on 17-May-21.
//

#ifndef MIVNEI_NETUNIM_EX1_MINHEAP_H
#define MIVNEI_NETUNIM_EX1_MINHEAP_H

#include "MinHeapADT.h"

template<typename T> class MinHeap : public MinHeapADT<T> {
  private:
    /// Array of all elements provided.
    T *array;

    /// The *size* of the *array*.
    int size;

  public:
    /**
     * @brief Constructor, initializes the *array*.
     * @param numberOfElements the number of elements to set the *array*.
     */
    explicit MinHeap(int numberOfElements) {
        array = new T[numberOfElements];
        size  = numberOfElements;
    }

    /**
     * @brief Deletes the *minimal element* in the heap, and returns it.
     * @note After removing the *minimal element* from the heap, this method
     *       calls the *fixHeap(0)* method, in order to fix the heap afterwards.
     * @return the *minimal element* removed from the heap.
     * @see fixHeap(int)
     */
    T deleteMin() override { return nullptr; }

    /**
     * @brief Inserts the @p elementToInsert to the heap.
     * @param elementToInsert the element to insert to the heap.
     */
    void insert(T elementToInsert) override {}

    /**
     * @brief Inserts the @p elementToInsert to the heap.
     * @param indexToFixFrom fixes the heap from this index downwards until the
     *                       leaves of the heap.
     * @note this method will continue to run until the root is no longer
     *       larger than one of his children, or when the root is a leaf.
     */
    void fixHeap(int indexToFixFrom) override {}

    /**
     * @brief Builds a **Minimum-Heap** by giving an arrayToBuildFrom of
     *        elements as a parameter.
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     */
    void buildHeap(T *arrayToBuildFrom) override {}
};

#endif //MIVNEI_NETUNIM_EX1_MINHEAP_H
