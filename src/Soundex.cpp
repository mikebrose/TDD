#include "Soundex.hpp"
#include <string>

std::string Soundex::Encode(const std::string& word) const {

    return ZeroPad(Head(word) + EncodeDigits(word));
}

std::string Soundex::Head(const std::string& word) const {
    return word.substr(0,1);
}

std::string Soundex::EncodeDigits(const std::string& word) const {
    
    if (word.length() > 1){
        //This will be more general soon
        return EncodeDigit();
    }
    return "";
}

std::string Soundex::EncodeDigit() const {
    return "1";
}




std::string Soundex::ZeroPad(const std::string& word) const {
    auto zerosNeeded = MAX_CODE_LENGTH - word.length();
    return word + std::string(zerosNeeded, '0');
}

