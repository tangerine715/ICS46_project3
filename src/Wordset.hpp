#ifndef __WORD_SET___HPP
#define __WORD_SET___HPP

#include <cmath>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>

namespace shindler::ics46::project3 {

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.

// To get the "number" that a letter-digit represents,
// subtract 'a' from it.
// e.g., (s[0]-'a') is the most significant "digit" of s.
// That would give you a 0 for a, etc;  add one to get 'a' = 1, 'b' = 2, etc.

// After every "digit" is processed, mod the current value by mod.
// This will keep you from having overflow.
[[nodiscard]] size_t polynomialHashFunction(const std::string &string,
                                            unsigned base, unsigned mod);

// These are value template parameters. You can pass in a value rather than a
// type into the parameter and use its value. This allows them to be set
// dynamically rather than having static constants within the class.
// Think of them as class constants (you can just use them like a variables
// named H1, H2, and EvictThreshold)
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
class BaseWordSet {
   private:
   std::string* buf1;
   std::string* buf2;
   unsigned int length;
    // You may declare private functions and member variables here.


   public:
    explicit BaseWordSet(size_t initialCapacity);
    ~BaseWordSet();

    // You do not need to worry about implementing these. They are only
    // here to ensure that we let the compiler know these functions
    // should not exist.
    BaseWordSet(const BaseWordSet &) = delete;
    BaseWordSet(BaseWordSet &&) = delete;
    BaseWordSet &operator=(const BaseWordSet &) = delete;
    BaseWordSet &operator=(BaseWordSet &&) = delete;

    // adds the given string to the WordSet, so that any
    // future calls to contains(s) will return true, unless that is later
    // removed.
    std::pair<std::string, unsigned int> insert_until_evict(const std::string &string);

    void insert_or_resize(const std::string &string, const std::string* old1, const std::string* old2, unsigned int &old_length);

    void insert(const std::string &string);

    void fully_insert_or_resize(const std::string &string,
const std::string* old1, const std::string* old2, unsigned int &old_length);

    void resize_and_rehash(std::string entry, const std::string* old1, const std::string* old2, unsigned int &old_length);

    [[nodiscard]] bool isPrime(int cur_length) const;

    [[nodiscard]] bool contains(const std::string &string) const;

    // return how many distinct strings are in the set
    [[nodiscard]] size_t size() const noexcept;

    // return how large the underlying array is.
    [[nodiscard]] size_t capacity() const noexcept;

    void erase(const std::string &string);
};

// You Should not use anything within the _impl namespace in your code.
// Instead reference the H1, H2, and EvictThreshold template parameters
namespace _impl {
const static unsigned int BASE_H1 = 37;
const static unsigned int BASE_H2 = 41;
const unsigned int BASE_EVICTION_THRESHOLD = 5;
}  // namespace _impl

// Add a usings statement with the default values for the project.
using WordSet =
    BaseWordSet<_impl::BASE_H1, _impl::BASE_H2, _impl::BASE_EVICTION_THRESHOLD>;

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
BaseWordSet<H1, H2, EvictThreshold>::BaseWordSet(size_t initialCapacity)
: buf1(new std::string[initialCapacity])
, buf2(new std::string[initialCapacity])
, length(initialCapacity)
{
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
BaseWordSet<H1, H2, EvictThreshold>::~BaseWordSet() {
    delete[] buf1;
    delete[] buf2;
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
std::pair<std::string, unsigned int> BaseWordSet<H1, H2, EvictThreshold>::insert_until_evict(const std::string &string) {
    unsigned int counter = 0;
    std::string string_to_be_inserted = string;
    std::string string_to_be_yeeted = buf1[shindler::ics46::project3::polynomialHashFunction
        (string_to_be_inserted, H1, length)];
    std::string string_in_yeet_position = buf2[shindler::ics46::project3::polynomialHashFunction
        (string_to_be_yeeted, H2, length)];
    bool finished = false;
    // std::cout << "ENTERING WHILE LOOP :: insert" << std::endl;
    while (counter < EvictThreshold && !finished)
    {
        if (string_in_yeet_position.empty())
        {
            finished = true;
        }
        //string to be inserted enters buf1 / buf2 of that value (depending on counter)
        if (counter % 2 == 0) {
            buf1[shindler::ics46::project3::polynomialHashFunction
        (string_to_be_inserted, H1, length)] = string_to_be_inserted;
        }
        else {
            buf2[shindler::ics46::project3::polynomialHashFunction
        (string_to_be_inserted, H2, length)] = string_to_be_inserted;
        }
        //string to be inserted = string to be yeeted
        string_to_be_inserted = string_to_be_yeeted;
        //string to be yeeted enters string in yeet position
        if (counter % 2 == 0) {
            buf2[shindler::ics46::project3::polynomialHashFunction
        (string_to_be_yeeted, H2, length)] = string_to_be_yeeted;
        }
        else {
            buf1[shindler::ics46::project3::polynomialHashFunction
        (string_to_be_yeeted, H1, length)] = string_to_be_yeeted;
        }
        //string to be yeeted = string in yeet position
        string_to_be_yeeted = string_in_yeet_position;
        //string in yeet position = buf1 / buf2 (depending on counter) of same thing
        if (counter % 2 == 0) {
            string_in_yeet_position = buf1[shindler::ics46::project3::polynomialHashFunction
        (string_to_be_yeeted, H1, length)];
        }
        else {
            string_in_yeet_position = buf2[shindler::ics46::project3::polynomialHashFunction
        (string_to_be_yeeted, H2, length)];
        }

        ++counter;
    }
    
    return {string_to_be_inserted, counter};
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::insert_or_resize(const std::string &string,
const std::string* old1, const std::string* old2, unsigned int &old_length) {
    auto [entry, counter] = insert_until_evict(string);
    if (counter >= EvictThreshold) //so we never finished inserting
    {
        auto oldold1 = new std::string[old_length];
        auto oldold2 = new std::string[old_length];
        for (unsigned int i = 0; i < old_length; ++i)
        {
            oldold1[i] = old1[i];
            oldold2[i] = old2[i];
        }
        unsigned int oldold_length = old_length;
        std::cout << "ABOUT TO RESIZE AND REHASH BC OF " << string << " WITH CUR CAP " << length << std::endl;
        resize_and_rehash(entry, oldold1, oldold2, oldold_length); //this also inserts
        std::cout << "SUCCESS OF " << string << " WITH CUR CAP " << length << std::endl;
        delete[] oldold1;
        delete[] oldold2;
    }
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::fully_insert_or_resize(const std::string &string,
const std::string* old1, const std::string* old2, unsigned int &old_length) {
    unsigned int val = shindler::ics46::project3::polynomialHashFunction(string, H1, length);
    // unsigned int val2 = shindler::ics46::project3::polynomialHashFunction(string, H2, length);
    // std::cout << "the H1 hash of " << string << " is " << val << std::endl;
    // std::cout << "the H2 hash of " << string << " is " << val2 << std::endl;
    // std::cout << "the current capacity is " << length << std::endl;
    if (buf1[val].empty())
    {
        buf1[val] = string;
    }
    else
    {
        insert_or_resize(string, old1, old2, old_length);
    }
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::insert(const std::string &string) {
    fully_insert_or_resize(string, buf1, buf2, length);
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::resize_and_rehash(std::string entry, const std::string* old1, const std::string* old2, unsigned int &old_length) {
    //old1, old2, and old_length ARE the copies, treat them as such
    //keep editing buf while preserving old1 and old2
    unsigned int new_length = 2*length;
    for (; !isPrime(new_length); ++new_length) { }

    buf1 = new std::string[new_length];
    buf2 = new std::string[new_length];
    length = new_length;

    for (unsigned int i = 0; i < old_length && length == new_length; ++i)
    {
        if(!old1[i].empty())
        {
            fully_insert_or_resize(old1[i], old1, old2, old_length);
            // insert(old_buf1[i]);
        }
        if (length != new_length) { break; }
        if(!old2[i].empty())
        {
            fully_insert_or_resize(old2[i], old1, old2, old_length);
            // insert(old_buf2[i]);
        }
    }
    fully_insert_or_resize(entry, old1, old2, old_length);
    // insert(entry);
}



template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
bool BaseWordSet<H1, H2, EvictThreshold>::isPrime(int cur_length) const {
    for (int i = 2; i <= std::sqrt(cur_length); ++i)
    {
        if (cur_length%i == 0) { return false; }
    }
    return true; 
}



template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
bool BaseWordSet<H1, H2, EvictThreshold>::contains(
    const std::string &string) const {
    unsigned int val1 = shindler::ics46::project3::polynomialHashFunction(string, H1, length);
    unsigned int val2 = shindler::ics46::project3::polynomialHashFunction(string, H2, length);
    //more efficient: check 1st then calculate 2nd
    //do this on everything
    return (buf1[val1] == string || buf2[val2] == string);
}

// return how many distinct strings are in the set
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
size_t BaseWordSet<H1, H2, EvictThreshold>::size() const noexcept {
    int counter{};
    for (unsigned int i = 0; i < length; ++i) 
    {
        if (!buf1[i].empty()) { ++counter; }
        if (!buf2[i].empty()) { ++counter; }
    }
    return counter;
}

// return how large the underlying array is.
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
size_t BaseWordSet<H1, H2, EvictThreshold>::capacity() const noexcept {
    return length;
    //lol im not making this O(n)
    //check if allowed or if i haaave to loop until '\0'
}

// removes this word if it is in the wordset.
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::erase(const std::string &string) {
    unsigned int val1 = shindler::ics46::project3::polynomialHashFunction(string, H1, length);
    unsigned int val2 = shindler::ics46::project3::polynomialHashFunction(string, H2, length);
    if (buf1[val1]==string) { buf1[val1] = ""; }
    else if (buf2[val2]==string) { buf2[val2] = ""; }
}

}  // namespace shindler::ics46::project3

#endif
