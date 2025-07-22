#ifndef __WORD_SET___HPP
#define __WORD_SET___HPP

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
    void insert(const std::string &string);

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
void BaseWordSet<H1, H2, EvictThreshold>::insert(const std::string &string) {
    // TODO: Implement this
    //hahahhahaahah no
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
    for (int i = 0; i < length; ++i) 
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
