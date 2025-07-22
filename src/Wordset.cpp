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
    // TODO: Implement this. You may remove the stub (it is only here
    //       to allow it to compile).
    std::string alpha = "abcdefghijklmnopqrstuvwxyz"; //check if you need other chars too
    std::vector<char> chars{alpha.begin(), alpha.end()};
    std::map<char, unsigned> enumerated{};
    unsigned counter = 1;
    for (char chr : chars)
    {
        enumerated[chr] = counter;
        ++counter;
    }

    counter = 0;
    unsigned total = 0;
    for (char chr : string)
    {
        total = (total + static_cast<unsigned int>(enumerated[chr] * pow(base, counter)) % mod) % mod;
        ++counter;
    }
    return total;
}

}  // namespace shindler::ics46::project3
