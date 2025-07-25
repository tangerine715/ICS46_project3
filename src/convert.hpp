#ifndef ___PROJECT_3_CONVERT_HPP
#define ___PROJECT_3_CONVERT_HPP

#include <istream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

#include "Wordset.hpp"

namespace shindler::ics46::project3 {

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
[[nodiscard]] std::vector<std::string> convert(const std::string& start,
                                               const std::string& end,
                                               const BaseWordSet<H1, H2, EvictThreshold>& words) {
    std::queue<std::string> frontier{};
    std::vector<std::string> final_vector{};
    //return empty vector if string lengths are different
    if (!(start.length() == end.length() && words.contains(start) && words.contains(end))) 
    { 
        return final_vector; 
    }
    //return vector with just the word if start and end are equal
    if (words.contains(start) && start == end) //edge case, probably happens anyway
    {
        final_vector.push_back(start);
        return final_vector;
    }

    std::unordered_map<std::string, std::string> explored{};
    frontier.push(start);
    std::string current_vertex{};
    bool found_the_end = false;

    while(!frontier.empty() && !found_the_end)
    {
        current_vertex = frontier.front();
        frontier.pop();

        std::string word = current_vertex;
        
        //for every character in the string
        for (size_t i = 0; i < current_vertex.length() && !found_the_end; ++i)
        {
            char og_char = word[i];
            //for every character it could be
            for (char chr = 'a'; chr <= 'z' && !found_the_end; ++chr) 
            {
                word[i] = chr;
                if(chr != og_char && words.contains(word))
                {
                    frontier.push(word);
                    explored.insert(current_vertex, word);
                    found_the_end = (word == end);
                }
            }
            //revert the word back to the original
            word[i] = og_char;
        }
    }
    if (found_the_end)
    {
        current_vertex = start;
        while (!explored.empty())
        {
            final_vector.push_back(current_vertex);
            current_vertex = explored[current_vertex];
            explored.erase(current_vertex);
        }
    }
    return final_vector;
}

// template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
// [[nodiscard]] bool distanceIsOne(const std::string& cur, const std::string& next) {
//     bool one_is_different = false;
//     size_t len = cur.length();
//     if (len != next.length()) { return false; } //could prob do smtn else idk
//     for (size_t i = 0; i < len; ++i)
//     {
//         if (cur.at(i) != next.at(i))
//         {
//             if (one_is_different) { return false; }
//             one_is_different = true;
//         }
//     }
//     return one_is_different;
// }


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
