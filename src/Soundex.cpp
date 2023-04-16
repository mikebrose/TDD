#include "Soundex.hpp"
#include <string>

std::string Soundex::Encode(const std::string& word) const {
    return ZeroPad(word);
}

std::string Soundex::ZeroPad(const std::string& word) const {
    return word + "000";
}