#include "Soundex.hpp"
#include <string>

std::string Soundex::Encode(const std::string& word) const {
    int len = word.length();
    if (len <= 0) {return std::string(" ");}
    std::string encoded;
    encoded += word.at(0);
    return encoded;
}