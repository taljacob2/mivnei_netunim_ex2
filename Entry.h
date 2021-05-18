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
 * @tparam K the *key* of the entry.
 * @tparam V the *value* of the entry.
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
template<typename K, typename V> class Entry {
  private:
    /// The *key* of the entry.
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

    K getKey() const { return key; }

    void setKey(K key) { this->key = key; }

    V getValue() const { return value; }

    void setValue(V value) { this->value = value; }

    /**
     * @brief std::ostream *operator <<* print method.
     */
    friend std::ostream &operator<<(std::ostream &os, const Entry &entry) {
        os << "key: " << entry.key << ", value: " << entry.value;
        return os;
    }
};


#endif //MIVNEI_NETUNIM_EX2_ENTRY_H
