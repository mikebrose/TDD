#include "Soundex.hpp"
#include <string>
#include <cstring>
#include <unordered_map>

std::string Soundex::encode(const std::string &word) const
{
    return zeroPad(upperFront(head(word)) + tail(encodeDigits(word)));
}

std::string Soundex::head(const std::string &word) const
{
    return word.substr(0, 1);
}

// Returns all of string after first character
std::string Soundex::tail(const std::string &word) const
{
    return word.substr(1);
}

std::string Soundex::encodeDigits(const std::string &word) const
{
    std::string encoding;
    encodeHead(encoding, word);
    encodeTail(encoding, word);
    return encoding;
}

void Soundex::encodeHead(std::string &encoding, const std::string &word) const
{
    encoding += mapLetterToDigit(word.front());
}

void Soundex::encodeTail(std::string &encoding, const std::string &word) const
{
    for (uint i = 1u; i < word.length(); i++)
    {
        if (!isComplete(encoding))
        {
            encodeLetter(encoding, word[i], word[i - 1]);
        }
    }
}

void Soundex::encodeLetter(std::string &encoding, char letter,
                           char last_letter) const
{
    std::string new_encoding = mapLetterToDigit(letter);
    if ((new_encoding != NOT_A_DIGIT) &&
        ((new_encoding != lastEncoding(encoding)) || isVowel(last_letter)))
    {
        encoding += new_encoding;
    }
}

bool Soundex::isVowel(const char letter) const
{
    return (std::string("aeiouy").find(std::tolower(letter)) != std::string::npos);
}

std::string Soundex::mapLetterToDigit(char letter) const
{
    const std::unordered_map<char, std::string> encodings{
        {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},

        {'c', "2"},
        {'g', "2"},
        {'j', "2"},
        {'k', "2"},
        {'q', "2"},
        {'s', "2"},
        {'x', "2"},
        {'z', "2"},

        {'d', "3"},
        {'t', "3"},

        {'l', "4"},

        {'m', "5"},
        {'n', "5"},

        {'r', "6"}};

    // will be end() if didnt find it
    auto lower_letter = std::tolower(static_cast<unsigned char>(letter));
    auto it = encodings.find(lower_letter);
    if (it == encodings.end())
    {
        return NOT_A_DIGIT;
    }
    else
    {
        return it->second;
    }
}

bool Soundex::isComplete(const std::string &encoding) const
{
    return (encoding.length() >= (MAX_CODE_LENGTH));
}

std::string Soundex::zeroPad(const std::string &word) const
{
    auto zerosNeeded = MAX_CODE_LENGTH - word.length();
    return word + std::string(zerosNeeded, '0');
}

std::string Soundex::lastEncoding(const std::string &encoding) const
{
    if (encoding.empty())
    {
        return NOT_A_DIGIT;
    }
    else
        return std::string(1, encoding.back());
}

std::string Soundex::upperFront(const std::string &letter) const
{
    return std::string(1,
                       std::toupper(static_cast<unsigned char>(letter.front())));
}
