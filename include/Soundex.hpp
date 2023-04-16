#ifndef _SOUNDEX_
#define _SOUNDEX_

#include <string>

class Soundex {
public:
    Soundex() {};

    std::string Encode(const std::string& word) const;
    std::string ZeroPad(const std::string& word) const;
};

#endif