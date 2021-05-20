//
// Created by Tal on 17-May-21.
//

#ifndef MIVNEI_NETUNIM_EX2_MINHEAP_H
#define MIVNEI_NETUNIM_EX2_MINHEAP_H

#include "MinHeapADT.h"
#include "my_algorithms.h"
#include <exception>
#include <ostream>
#include <stdexcept>
#include <string>

/**
 * @brief This class implements a **Minimum-Heap** which its elements are
 *        pointers to *Entries* that are composed by a *key* and a *value*.
 *
 * The heap compares its elements to each other, by the comparable `key` field
 * located in each `Entry` element.
 * @tparam K the type of *key* in the entry.
 * @tparam V the type of *value* in the entry.
 * @note The terms `element`, `node` and 'entry' are synonyms.
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 * @see Entry
 */
template<typename K, typename V> class MinHeap : public MinHeapADT<K, V> {
  private:
    /**
     * Array of pointers to `Entries` that serve as `elements`.
     * Initialized to `nullptr`.
     */
    Entry<K, V> **array = nullptr;

    /// The *physical-size* of the *array*.
    int physicalSize = 0;

    /// The *logical-size* of the *array*.
    int logicalSize = 0;

  public:
    /**
     * @brief Constructor, initializes the *array*.
     *
     * Builds a **Minimum-Heap** by giving an @p arrayToBuildFrom of
     * elements as a parameter. Done by invoking the @link buildHeap @endlink
     * method.
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     * @param sizeOfArrayToBuildFrom the size of the array to build the
     *                               heap from.
     * @see buildHeap
     */
    explicit MinHeap(Entry<K, V> *arrayToBuildFrom,
                     int          sizeOfArrayToBuildFrom) {
        buildHeap(arrayToBuildFrom, sizeOfArrayToBuildFrom);
    }

    /**
     * @brief Constructor, initializes the *array*.
     *
     * Builds a **Minimum-Heap** by giving an @p arrayToBuildFrom of
     * elements as a parameter. Done by invoking the @link buildHeap @endlink
     * method.
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     * @param sizeOfArrayToBuildFrom the size of the array to build the
     *                               heap from.
     * @see buildHeap
     */
    // explicit MinHeap(Entry<K, V> *arrayToBuildFrom,
    //                  int          sizeOfArrayToBuildFrom) {
    //     buildHeap(arrayToBuildFrom, sizeOfArrayToBuildFrom);
    // }

    MinHeap() = default;

    /**
     * @brief Destructor.
     */
    virtual ~MinHeap() {
        // for (int i = 0; i < physicalSize; i++) { delete array[i]; }
        delete[] array;
    }

    /**
     * @brief Deletes the *minimal element* from the heap, and returns it.
     *
     * @note After removing the *minimal element* from the heap, this method
     *       calls the *fixHeap(0)* method, in order to fix the heap afterwards.
     * @attention in case the `logicalSize` of the *array* is 0,
     *            this method returns `null_ptr`.
     * @return the *minimal element* removed from the heap.
     * @see fixHeap(int)
     */
    Entry<K, V> *deleteMin() override {

        /*
         * Returns the `first` element in the array (= the `minimal` element).
         * In case the `logicalSize` of the array is 0,
         * this method returns `nullptr`.
         */
        Entry<K, V> *returnElement = nullptr;
        if (logicalSize > 0) { returnElement = array[0]; }

        /* Set the `first` element in the array to be the `last` element. */
        array[0] = array[logicalSize - 1];

        /* Set the `last` element to be `nullptr`. */
        array[logicalSize - 1] = nullptr;

        /* Decrease the `logicalSize` of the array by `1`. */
        logicalSize--;

        /* Invoke `fixHeap(0)` to fix the heap. */
        fixHeap(0);

        return returnElement;
    }

    /**
     * @brief Inserts the @p elementToInsert to the heap.
     *
     * @param elementToInsert the element to insert to the heap.
     * @throws std::runtime_error in case the heap is already full.
     */
    void insert(Entry<K, V> *elementToInsert) override {

        /* If there is enough space in the array. */
        if (physicalSize > logicalSize) {

            /* Add the `elementToInsert` as the `last` element in the array. */
            array[logicalSize++] = elementToInsert;

            int currentIndex = logicalSize - 1;

            /*
             * Check upwards the heap, whether there is a need to `swap` the
             * elements according to the insertion, to ensure the heap is valid.
             * While there is at least `1` child in the array.
             */
            while (0 < currentIndex) {

                /*
                 * Beginning with the inserted element, compare each child to
                 * its parent, to check if there is a need to `swap` between
                 * them, in order to ensure validity of the heap, as a
                 * `Minimum-Heap`.
                 */
                if (*array[currentIndex] < *array[(currentIndex - 1) / 2]) {
                    my_algorithms::swap(array, currentIndex,
                                        (currentIndex - 1) / 2);

                    /* Step upwards to the parent of the element. */
                    currentIndex = (currentIndex - 1) / 2;
                } else {
                    break;
                }
            }
        } else {

            /* The heap is already full. Throw a message. */
            std::string message;
            message.append("The heap is already full, and contains ");
            message.append(std::to_string(physicalSize));
            message.append(" elements.");

            // TODO: change to `wrong input`
            throw std::runtime_error(message);
        }
    }

    /**
     * @brief This method handles a heap that is *valid* from the root downwards
     *        until the `indexToFixFrom`, which from there and on downwards,
     *        the heap is *invalid* - means: that the `node` in the
     *        `indexToFixFrom` is no smaller than both of its children.
     *
     * @param indexToFixFrom the method fixes the heap from this index
     *                       downwards until the leaves of the heap.
     * @note this method will continue to run until the root is no longer
     *       smaller than both of its children, or when the root is a leaf.
     * @attention there is no use to give @p indexToFixFrom that is larger
     *            than `(logicalSize / 2)`, because indexes larger than
     *            `(logicalSize / 2)` point to leaf `node`s, thus the method
     *            will have no effect, as explained earlier.
     * @throws std::out_of_range in case the index provided is out of range.
     */
    void fixHeap(int indexToFixFrom) override {

        /* Check that `indexToFixFrom` is a legal index. */
        if ((indexToFixFrom < 0) || (logicalSize <= indexToFixFrom)) {

            /* The `indexToFixFrom` is out of range. Throw a message. */
            std::string message;
            message.append("The index provided is out of range. There are ");
            message.append(std::to_string(logicalSize));
            message.append(" elements in the heap.");

            // TODO: change to `wrong input`
            throw std::out_of_range(message);
        }

        /*
         * `currentIndex` should be in between `0` and `(logicalSize / 2)`.
         *
         * Note: the `almost last` level has `(logicalSize / 2)` `nodes`.
         * Attention: there is no use to give `indexToFixFrom` that is larger
         *            than `(logicalSize / 2)`.
         */
        int currentIndex = indexToFixFrom;
        if (array[currentIndex] == nullptr) {

            /*
             * The `indexToFixFrom` is out of range. Throw a message.
             * Note: should not be happening here, thanks to already checked
             * scenario.
             */
            std::string message;
            message.append(
                    "The index provided is out of range. The element "
                    "you have provided is `nullptr`. Thus, in-comparable.");

            // TODO: change to `wrong input`
            throw std::out_of_range(message);
        }

        /* array[currentIndex] is not `nullptr`. Thus, comparable. */
        fixHeapWhile(currentIndex);
    }

  private:
    /**
     * @brief This method is a *private* method, that represents a `while`
     *        that is being invoked by the @link fixHeap(int) @endlink method.
     *
     * @param currentIndex should be in between `0` and `(logicalSize / 2)`.
     *                     Represents the index to *fixHeap* from.
     * @see fixHeap(int)
     */
    void fixHeapWhile(int currentIndex) {

        /* array[currentIndex] is not `nullptr`. Thus, comparable. */
        while ((0 <= currentIndex) && (currentIndex < (logicalSize / 2))) {

            /* Get the index that points to the `minimal` element. */
            int indexOfMinimalChildOfCurrentRoot =
                    my_algorithms::min(array, logicalSize, currentIndex * 2 + 1,
                                       currentIndex * 2 + 2);
            if (array[indexOfMinimalChildOfCurrentRoot] != nullptr) {

                /*
                 * There is a living entry.
                 * Compare by keys.
                 * `swap` the elements if needed, to maintain the validity of
                 * the heap as a `Minimum-Heap`.
                 */
                if (*array[currentIndex] >
                    *array[indexOfMinimalChildOfCurrentRoot]) {
                    my_algorithms::swap(array, currentIndex,
                                        indexOfMinimalChildOfCurrentRoot);

                    /*
                     * Set the updated iterator index to the replaced index.
                     * Note: this enlarges the index.
                     */
                    currentIndex = indexOfMinimalChildOfCurrentRoot;
                }
            } else {

                /*
                 * There is no entry to compare with.
                 * Thus, this `node` does not have children,
                 * and is actually a leaf.
                 */
                break;
            }
        }
    }

  public:
    /**
     * @brief Builds a **Minimum-Heap** by giving an @p arrayToBuildFrom of
     *        elements as a parameter.
     *
     * Done by making an array of pointers to the elements given in the @p
     * arrayToBuildFrom.
     * @param arrayToBuildFrom the given array of elements to build the
     *                         heap from.
     * @param sizeOfArrayToBuildFrom the size of the array to build the
     *                               heap from.
     */
    void buildHeap(Entry<K, V> *arrayToBuildFrom,
                   int          sizeOfArrayToBuildFrom) override {

        /* Delete the old array if there is any. */
        delete[] array;

        /* Initialize a `new` empty array of pointers to elements given. */
        physicalSize = sizeOfArrayToBuildFrom;
        logicalSize  = sizeOfArrayToBuildFrom;
        array        = new Entry<K, V> *[sizeOfArrayToBuildFrom];
        for (int i = 0; i < sizeOfArrayToBuildFrom; i++) {
            array[i] = &arrayToBuildFrom[i];
        }

        /*
         * `currentIndex` should be in between `0` and `(logicalSize / 2)`.
         * Note: the almost last level has `(logicalSize / 2)` `nodes`.
         */
        int lastIndex = logicalSize - 1;
        for (int currentIndex = (lastIndex - 1) / 2; currentIndex >= 0;
             currentIndex--) {
            fixHeap(currentIndex);
        }
    }

    /**
     * @brief returns a boolean value that determines whether this heap is
     *        empty or not.
     *
     * @return boolean value of *true* if the heap is empty, or else, *false* if
     *         the heap is not empty.
     */
    bool isEmpty() override { return logicalSize; }

    /**
     * @brief clears the heap from elements.
     */
    void makeEmpty() override { logicalSize = 0; }

    /**
     * @brief std::ostream `operator <<` print method.
     */
    friend std::ostream &operator<<(std::ostream &os, const MinHeap &heap) {
        os << "array{\n";
        for (int i = 0; i < heap.logicalSize; i++) {
            os << *heap.array[i];
            os << "\n";
        }
        os << "logicalSize: " << heap.logicalSize
           << ", physicalSize: " << heap.physicalSize << "\n}" << '\n';
        return os;
    }
};

#endif //MIVNEI_NETUNIM_EX2_MINHEAP_H
