//
// Created by Tal on 17-May-21.
//

#ifndef MIVNEI_NETUNIM_EX1_MINHEAPADT_H
#define MIVNEI_NETUNIM_EX1_MINHEAPADT_H

/**
 * This class represents an *abstract* **Minimum-Heap**.
 *
 * @tparam T type of element in the *Heap*.
 */
template<typename T> class MinHeapADT {

  public:
    /**
     * @brief Deletes the *minimal element* in the heap, and returns it.
     * @return the *minimal element* removed from the heap.
     */
    virtual T deleteMin() = 0;

    /**
     * @brief Inserts the @p elementToInsert to the heap.
     * @param elementToInsert the element to insert to the heap.
     */
    virtual void insert(T elementToInsert) = 0;

    /**
     * @brief Inserts the @p elementToInsert to the heap.
     * @param indexToFixFrom fixes the heap from this index downwards until the
     *                       leaves of the heap.
     * @note this method will continue to run until the root is no longer
     *       larger than one of his children, or when the root is a leaf.
     */
    virtual void fixHeap(int indexToFixFrom) = 0;

    /**
     * @brief Builds a **Minimum-Heap** by giving an array of elements as a
     *        parameter.
     * @param arrayToBuildFrom the given array of elements to build the heap from.
     */
    virtual void buildHeap(T *arrayToBuildFrom) = 0;
};


#endif //MIVNEI_NETUNIM_EX1_MINHEAPADT_H
