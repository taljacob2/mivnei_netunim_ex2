//
// Created by Tal on 30-Mar-21.
//

#include "my_string.h"

/// the max length of the string
static constexpr int MAX_LENGTH = 1024;

my_string::~my_string() { delete[] str; }
my_string::my_string(const my_string &other) : str(nullptr) {
    this->operator=(other.str);
}
my_string::my_string() : str(nullptr) {}
my_string::my_string(const char *other) : str(nullptr) {
    this->operator=(other);
}
int my_string::getLength() const {
    if (str == nullptr) { return 0; }
    else {
        return strlen(str);
    }
}
int my_string::compare(const char *&str1, const char *&str2) {
    bool str1_isNullptr = false;
    bool str2_isNullptr = false;

    if (str1[0] == '\0') {
        str1_isNullptr = true;
    }
    if (str2[0] == '\0') {
        str2_isNullptr = true;
    }

    // compare: if the `str` is nullptr send it to be the last.
    if ((!str1_isNullptr) && (!str2_isNullptr)) {
        return strcmp(str1, str2);
    } else if ((!str1_isNullptr) && (str2_isNullptr)) {
        return -1;
    } else if ((str1_isNullptr) && (!str2_isNullptr)) {
        return 1;
    } else if ((str1_isNullptr) && (str2_isNullptr)) {
        return 0;
    }
    return 0; // in case of an ERROR.
}
int my_string::compare(const my_string &str1, const my_string &str2) {
    bool str1_isNullptr = false;
    bool str2_isNullptr = false;

    if (str1.getLength() == 0) {
        str1_isNullptr = true;
    }
    if (str2.getLength() == 0) {
        str2_isNullptr = true;
    }

    // compare: if the `str` is nullptr send it to be the last.
    if ((!str1_isNullptr) && (!str2_isNullptr)) {
        return strcmp(str1, str2);
    } else if ((!str1_isNullptr) && (str2_isNullptr)) {
        return -1;
    } else if ((str1_isNullptr) && (!str2_isNullptr)) {
        return 1;
    } else if ((str1_isNullptr) && (str2_isNullptr)) {
        return 0;
    }
    return 0; // in case of an ERROR.
}

/*+Operators+*/
my_string::operator char *() { return getStr(); }
my_string::operator char *() const { return getStr(); }
my_string::operator std::string() const {
    return (std::string) str;
}
my_string &my_string::operator=(const char *other) {
    if (str != nullptr) {

        //overwriting:
        delete[] str; //destruct original
    }
    if (other != nullptr) {
        str = new char[strlen(other) + 1];
        for (int i = 0; (str[i] = other[i]); i++) {}
    } else {
        str = new char[1];
        str[0] = '\0';
    }
    return *this;
}
my_string &my_string::operator=(const my_string &other) {
    if (&other != this) {//only if they are different
        if (str != nullptr) {

            //overwriting:
            delete[]str; //destruct original
        }
        int otherLength = other.getLength();
        str = new char[otherLength + 1];
        if (otherLength > 0) {
            for (int i = 0; (str[i] = other.str[i]); i++) {}
        } else {
            str[0] = '\0';
        }
    }
    return *this;
}
bool my_string::operator==(const my_string &other) const {
    return !compare(*this, other);
}
bool my_string::operator!=(const my_string &other) const {
    return compare(*this, other);
}
bool my_string::operator<(const my_string &other) const {
    return compare(*this, other) < 0;
}
bool my_string::operator<=(const my_string &other) const {
    return compare(*this, other) <= 0;
}
bool my_string::operator>(const my_string &other) const {
    return compare(*this, other) > 0;
}
bool my_string::operator>=(const my_string &other) const {
    return compare(*this, other) >= 0;
}

/*+FRIEND+*/
std::ostream &operator<<(std::ostream &os, const my_string &my_str) {
    std::cout << my_str.str;
    return os;
}
std::istream &operator>>(std::istream &is, my_string &my_str) {

    // indicates whether we have encountered `white-spaces`:
    bool whiteSpacesEncountered = false;
    char tmpStr[MAX_LENGTH];
    int buffer = 0;
    int i = 0;
    for (; buffer < MAX_LENGTH - 1; ++buffer) {
        char c = is.get();
        if ((c == ' ') || (c == '\t')) {
            whiteSpacesEncountered = true;
        }

        // stop receiving right before engaging `\n`:
        if (c == '\n') {
            break;
        }

        /*
         * if we have already encountered `white-spaces`,
         * break right after receiving a `non-whitespace`.
         */
        if ((whiteSpacesEncountered) && (c != ' ') && (c != '\t')) {
            is.unget(); // un-get the `non-whitespace` back to stream.
            break;
        }
        if (!whiteSpacesEncountered) {
            tmpStr[i] = c;
            ++i;
        }
    }

    // if this string was only `white-spaces`, continue receiving from stream.
    if (i == 0) {
        is >> my_str;
    } else {
        tmpStr[i] = '\0';
        my_str = tmpStr;
    }
    return is;
}

/*+File functions+*/
bool my_string::save(std::ostream &out) const {
    int len = getLength();
    out.write(reinterpret_cast<const char *>(&len), sizeof(int));
    out.write(reinterpret_cast<const char *>(str), len);
    return out.good();
}
bool my_string::load(std::istream &in) {
    int len;
    in.read(reinterpret_cast<char *>(&len), sizeof(len));
    delete[]str;
    str = new char[len + 1];
    in.read(reinterpret_cast<char *>(str), len);
    str[len] = '\0';
    return in.good();
}
