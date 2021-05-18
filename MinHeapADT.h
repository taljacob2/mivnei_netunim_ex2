//
// Created by Tal on 17-May-21.
//

#ifndef MIVNEI_NETUNIM_EX2_MINHEAPADT_H
#define MIVNEI_NETUNIM_EX2_MINHEAPADT_H

/**
 * @brief This class represents an *abstract* **Minimum-Heap**.
 *
 * @tparam T type of element in the *Heap*.
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
template<typename T> class MinHeapADT {

  public:
    /**
     * @brief Deletes the *minimal element* in the heap, and returns it.
     *
     * @return the *minimal element* removed from the heap.
     */
    virtual T *deleteMin() = 0;

    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param elementToInsert the element to insert to the heap.
     */
    virtual void insert(T &elementToInsert) = 0;

    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param indexToFixFrom fixes the heap from this index downwards until the
     *                       leaves of the heap.
     * @note this method will continue to run until the root is no longer
     *       larger than one of his children, or when the root is a leaf.
     */
    virtual void fixHeap(int indexToFixFrom) = 0;

    /**
     * @brief Builds a **Minimum-Heap** by giving an arrayToBuildFrom of
     *        elements as a parameter.
     *
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     */
    virtual void buildHeap(T *arrayToBuildFrom, int sizeOfArrayToBuildFrom) = 0;

    /**
     * @brief boolean value whether this heap empty or not.
     * @return boolean value. *true* if the heap is empty, *false* if the
     *         heap is not empty.
     */
    virtual bool isEmpty() = 0;

    /**
     * @brief clears the heap from elements.
     */
    virtual void makeEmpty() = 0;
};


#endif //MIVNEI_NETUNIM_EX2_MINHEAPADT_H
