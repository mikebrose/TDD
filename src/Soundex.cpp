#include "Soundex.hpp"
#include <string>
#include <unordered_map>

std::string Soundex::Encode(const std::string& word) const {

    return ZeroPad(Head(word) + EncodeDigits(word));
}

std::string Soundex::Head(const std::string& word) const {
    return word.substr(0,1);
}

std::string Soundex::EncodeDigits(const std::string& word) const {
    
    if (word.length() > 1){
        //This will be more general soon
        return EncodeDigit(word[1]);
    }
    return "";
}

std::string Soundex::EncodeDigit(char letter) const {
    const std::unordered_map<char, std::string> encodings {
        {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"}, 

        {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, 
        {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"}, 

        {'d', "3"}, {'t', "3"},

        {'l', "4"},

        {'m', "5"}, {'n', "5"},

        {'r', "6"}
    };

    //will be end() if didnt find it
    auto it = encodings.find(letter);
    if (it == encodings.end()){
        return "0";
    } else {
        return it->second;
    }
}




std::string Soundex::ZeroPad(const std::string& word) const {
    auto zerosNeeded = MAX_CODE_LENGTH - word.length();
    return word + std::string(zerosNeeded, '0');
}

