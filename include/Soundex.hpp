#ifndef _SOUNDEX_
#define _SOUNDEX_

#include <string>

static const uint MAX_CODE_LENGTH = 4;
class Soundex {
public:
    Soundex() {};
    std::string Encode(const std::string& word) const;

private:
    std::string Head(const std::string& word) const;
    std::string EncodeDigits(const std::string& word) const;
    std::string EncodeDigit(char letter) const;
    std::string ZeroPad(const std::string& word) const;
    std::string Tail(const std::string& word) const;
};

#endif