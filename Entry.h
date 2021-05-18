//
// Created by Tal on 18-May-21.
//

#ifndef MIVNEI_NETUNIM_EX2_ENTRY_H
#define MIVNEI_NETUNIM_EX2_ENTRY_H

#include <ostream>
/**
 * @brief This class represents a general *entry*, which is composed from a
 * *key* and a *value*.
 *
 * `Entries` are compared to each other, by the comparable `key` field
 * located in each `Entry` element.
 * @attention the `key` **must** be `comparable`.
 * @tparam K the type of *key* in the entry.
 * @tparam V the type of *value* in the entry.
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
template<typename K, typename V> class Entry {
  private:
    /// The *key* of the entry. @attention **Must** be `comparable`.
    K key;

    /// The *value* of the entry.
    V value;

  public:
    /**
     * @brief Initializer constructor.
     *
     * @param key the key to set the entry with.
     * @param value the value to set the entry with.
     */
    Entry(K key, V value) {
        this->key   = key;
        this->value = value;
    }

    /**
     * @brief Empty default constructor.
     */
    Entry() = default;

    /* -- Getters & Setters -- */

    K getKey() const { return key; }

    void setKey(K key) { this->key = key; }

    V getValue() const { return value; }

    void setValue(V value) { this->value = value; }

    /* -- Operators -- */

    /**
     * @brief std::ostream `operator <<` print method.
     */
    friend std::ostream &operator<<(std::ostream &os, const Entry &entry) {
        os << "key: " << entry.key << ", value: " << entry.value;
        return os;
    }

    bool operator<(const Entry &other) const { return (key < other.key); }

    bool operator>(const Entry &other) const { return (key > other.key); }

    bool operator<=(const Entry &other) const { return !(other < *this); }

    bool operator>=(const Entry &other) const { return !(*this < other); }

    bool operator==(const Entry &other) const { return key == other.key; }

    bool operator!=(const Entry &other) const { return !(other == *this); }
};


#endif //MIVNEI_NETUNIM_EX2_ENTRY_H
