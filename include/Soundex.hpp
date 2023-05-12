#ifndef _SOUNDEX_
#define _SOUNDEX_

#include <string>

static const uint MAX_CODE_LENGTH = 4;
class Soundex
{
public:
    Soundex(){};
    std::string encode(const std::string &word) const;
    std::string mapLetterToDigit(char letter) const;
    std::string myFunction(const std::string &letter) const;

private:
    void encodeHead(std::string &encoding, const std::string &word) const;
    void encodeTail(std::string &encoding, const std::string &word) const;
    std::string head(const std::string &word) const;
    std::string encodeDigits(const std::string &word) const;
    void encodeLetter(std::string &encoding, char letter, char last_letter) const;
    std::string zeroPad(const std::string &word) const;
    std::string tail(const std::string &word) const;
    bool isComplete(const std::string &encoding) const;
    bool isVowel(const char letter) const;
    std::string lastEncoding(const std::string &encoding) const;
    std::string upperFront(const std::string &letter) const;

    std::string last_encoding;
    const std::string NOT_A_DIGIT{"*"};
};

#endif