#include "Wordset.hpp"

#include <map>
#include <string>
#include <vector>
#include <ranges>
#include <cmath>

namespace shindler::ics46::project3 {

// returns s, as a number in the given base, mod the given modulus
size_t polynomialHashFunction(const std::string &string, unsigned int base,
                              unsigned int mod) {
    unsigned int hash = 0;
    unsigned int power = base + 1 - base;
    for (size_t i = 0; i < string.size(); ++i)
    {
        char chr = string[string.length()-i-1];
        hash = (hash + ((static_cast<unsigned int>(chr-'a'+1))%mod) * power) % mod; 
        // power = (power*base) % mod;
    }
    return hash;
}

}  // namespace shindler::ics46::project3
