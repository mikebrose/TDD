#include "Soundex.hpp"
#include <string>
#include <cstring>
#include <unordered_map>

std::string Soundex::Encode(const std::string& word) const {

    return ZeroPad(UpperFront(Head(word)) + EncodeDigits(Tail(word)));
}

std::string Soundex::Head(const std::string& word) const {
    return word.substr(0,1);
}

// Returns all of string after first character
std::string Soundex::Tail(const std::string& word) const {
    return word.substr(1);
}

std::string Soundex::EncodeDigits(const std::string& word) const {
    std::string encoding;
    for (auto letter : word){
        if (IsComplete(encoding)){
            break;
        }

        std::string new_encoding = EncodeDigit(letter);
        // Will not add to the encoding if it wasn't a valid digit,
        // or is already at Max Code Length
        if ((new_encoding != NotADigit) && (new_encoding != LastEncoding(encoding))){
            encoding += new_encoding;
        }    
    }
    return encoding;
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
        return NotADigit;
    } else {
        return it->second;
    }
}

bool Soundex::IsComplete(const std::string& encoding) const {
    return (encoding.length() >= (MAX_CODE_LENGTH - 1));
}


std::string Soundex::ZeroPad(const std::string& word) const {
    auto zerosNeeded = MAX_CODE_LENGTH - word.length();
    return word + std::string(zerosNeeded, '0');
}

std::string Soundex::LastEncoding(const std::string& encoding) const {
    if (encoding.empty()) {
        return NotADigit;
    }
    else return std::string(1, encoding.back());
}

std::string Soundex::UpperFront(const std::string& letter) const {
    return std::string(1,
        std::toupper(static_cast<unsigned char>(letter.front())));
}
