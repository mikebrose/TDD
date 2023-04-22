#ifndef _SOUNDEX_
#define _SOUNDEX_

#include <string>

static const uint MAX_CODE_LENGTH = 4;
class Soundex
{
public:
    Soundex(){};
    std::string Encode(const std::string &word) const;
    std::string MapLetterToDigit(char letter) const;
    std::string MyFunction(const std::string &letter) const;

private:
    void EncodeHead(std::string &encoding, const std::string &word) const;
    void EncodeTail(std::string &encoding, const std::string &word) const;
    std::string Head(const std::string &word) const;
    std::string EncodeDigits(const std::string &word) const;
    void EncodeLetter(std::string &encoding, char letter) const;
    std::string ZeroPad(const std::string &word) const;
    std::string Tail(const std::string &word) const;
    bool IsComplete(const std::string &encoding) const;
    std::string LastEncoding(const std::string &encoding) const;
    std::string UpperFront(const std::string &letter) const;
    std::string last_encoding;

    const std::string NotADigit{"*"};
};

#endif