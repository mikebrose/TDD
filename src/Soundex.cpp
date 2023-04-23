#include "Soundex.hpp"
#include <string>
#include <cstring>
#include <unordered_map>

std::string Soundex::Encode(const std::string& word) const {

    return ZeroPad(UpperFront(Head(word)) + Tail(EncodeDigits(word)));
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
    EncodeHead(encoding, word);
    EncodeTail(encoding, word);
    return encoding;
}

void Soundex::EncodeHead(std::string& encoding, const std::string& word) const {
     encoding += MapLetterToDigit(word.front());
}

void Soundex::EncodeTail(std::string& encoding, const std::string& word) const {
    for (uint i = 1u; i < word.length(); i++){
        if (!IsComplete(encoding)){
            EncodeLetter(encoding, word[i], word[i-1]);
        }
    }
}

void Soundex::EncodeLetter(std::string &encoding, char letter, 
    char last_letter) const {

    std::string new_encoding = MapLetterToDigit(letter);
    if ( (new_encoding != NotADigit) &&
         ((new_encoding != LastEncoding(encoding)) || IsVowel(last_letter))) {
        encoding += new_encoding;
    }    
}

bool Soundex::IsVowel(const char letter) const {
    return (std::string("aeiouy").find(std::tolower(letter)) != std::string::npos);
}

std::string Soundex::MapLetterToDigit(char letter) const {
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
    auto lower_letter = std::tolower(static_cast<unsigned char>(letter));
    auto it = encodings.find(lower_letter);
    if (it == encodings.end()){
        return NotADigit;
    } else {
        return it->second;
    }
}

bool Soundex::IsComplete(const std::string& encoding) const {
    return (encoding.length() >= (MAX_CODE_LENGTH));
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

