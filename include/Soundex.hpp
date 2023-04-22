#ifndef _SOUNDEX_
#define _SOUNDEX_

#include <string>

static const uint MAX_CODE_LENGTH = 4;
class Soundex {
public:
    Soundex() {};
    std::string Encode(const std::string& word) const;
    std::string EncodeDigit(char letter) const;

private:
    std::string Head(const std::string& word) const;
    std::string EncodeDigits(const std::string& word) const;
    std::string ZeroPad(const std::string& word) const;
    std::string Tail(const std::string& word) const;
    bool IsComplete(const std::string& encoding) const;
    std::string LastEncoding(const std::string& encoding) const;
    std::string UpperFront(const std::string& letter) const;
    std::string last_encoding;

    const std::string NotADigit{"*"};
};

#endif