#ifndef ___PROJECT_3_CONVERT_HPP
#define ___PROJECT_3_CONVERT_HPP

#include <istream>
#include <string>
#include <vector>

#include "Wordset.hpp"

namespace shindler::ics46::project3 {

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
[[nodiscard]] std::vector<std::string> convert(const std::string& start,
                                               const std::string& end,
                                               const BaseWordSet<H1, H2, EvictThreshold>& words) {
    // TODO: Implement this. The stub is only to allow the code to remove
    //       (you can remove it).
    return {};
}

// You should not need to change this function
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void loadWordsIntoTable(std::istream& istream,
                        BaseWordSet<H1, H2, EvictThreshold>& words) {
    std::string word;

    while (istream >> word) {
        words.insert(word);
    }
}

}  // namespace shindler::ics46::project3

#endif
