//
// Created by Tal on 30-Mar-21.
//

#ifndef MIVNEI_NETUNIM_EX1_MY_STRING_H
#define MIVNEI_NETUNIM_EX1_MY_STRING_H

#include <cstring>
#include <iostream>
#include <fstream>

/**
 * @brief this is my implementation of the `string` class.
 *
 * @note the class is `iterable`.
 * @author Tal Yacob, ID: 208632778.
 * @version 2.0
 */
class my_string {

private:
    char *str;

public:
    my_string();
    ~my_string();
    my_string(const my_string &other);
    my_string(const char *other);
    char *&getStr() { return str; } // str is sent by reference.
    char *getStr() const { return str; } // str is sent by reference.
    int getLength() const;
    static int compare(const char *&str1, const char *&str2);
    static int compare(const my_string &str1, const my_string &str2);

    /*+Operators+*/
    operator char *();
    operator char *() const;
    explicit operator std::string() const;
    my_string &operator=(const char *other);
    my_string &operator=(const my_string &other);
    bool operator==(const my_string &other) const;
    bool operator!=(const my_string &other) const;
    bool operator<(const my_string &other) const;
    bool operator<=(const my_string &other) const;
    bool operator>(const my_string &other) const;
    bool operator>=(const my_string &other) const;

    /*+FRIEND+*/
    friend std::ostream &operator<<(std::ostream &os, const my_string &my_str);

    /**
     * @attention @arg this implementation enforces the `string` to **ignore**
     *                 the following `white-spaces`: @code ' ', '\t', '\n'
     *                 @endcode. and receives only `non-white-spaces`.
     * @attention @arg the method does **not** include the last @code '\n'
     *                 @endcode in the `string` and does **not** leave it
     *                 in the @p is @p istream.
     *                 instead, the method reads it but **ignores** it.
     * @param is the @p istream to read from.
     * @param my_str the `string` to read into.
     * @return the given @p is @p istream.
     */
    friend std::istream &operator>>(std::istream &is, my_string &my_str);

    /*+File functions+*/
    bool save(std::ostream &out) const;
    bool load(std::istream &in);

    /* +Iterator+ */
    class iterator {
    private:
        my_string *_myString;
        int _i;

    public:

        using iterator_category = std::bidirectional_iterator_tag;
        // other options exist, e.g., std::forward_iterator_tag
        using different_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char *;
        using reference = char &;

        // constructors:
        iterator(my_string &myString, int i) : _myString(&myString), _i(i) {}
        iterator(const iterator &other) : _myString(other._myString),
                                          _i(other._i) {}
        ~iterator() = default;

        // operator=
        iterator &operator=(const iterator &other) {
            if (this != &other) {
                if (other._myString == _myString) {
                    _i = other._i;
                }
            }
            return *this;
        }

        // comparison with another _iterator
        bool operator==(const iterator &other) const {
            return (_myString == other._myString) && (_i == other._i);
        }
        bool operator!=(const iterator &other) const {
            return !(*this == other);
        }
        bool operator<(const iterator &other) const {
            return _i < other._i;
        }
        bool operator>(const iterator &other) const {
            return _i > other._i;
        }
        bool operator<=(const iterator &other) const {
            return _i <= other._i;
        }
        bool operator>=(const iterator &other) const {
            return _i >= other._i;
        }

        // smart-pointer _iterator methods
        reference operator*() {
            return _myString->getStr()[_i];
        }
        pointer operator->() {
            return &_myString->getStr()[_i];
        }

        // increment-decrement _iterator methods
        iterator operator+(int num) const {
            return iterator(*_myString, _i + num);
        }
        iterator operator-(int num) const {
            return iterator(*_myString, _i - num);
        }
        iterator &operator++() {
            ++_i;
            return *this;
        }
        iterator operator++(int) {
            iterator temp(*this);
            ++_i;
            return temp;
        }
        iterator &operator--() {
            --_i;
            return *this;
        }
        iterator operator--(int) {
            iterator temp(*this);
            --_i;
            return temp;
        }
    };

    // begin / end:
    iterator begin() {
        return iterator(*this, 0);
    }
    iterator end() {
        return iterator(*this, this->getLength());
    }
};

#endif //MIVNEI_NETUNIM_EX1_MY_STRING_H