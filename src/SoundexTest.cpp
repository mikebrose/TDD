#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Soundex.hpp"
#include <string>

using testing::Eq;

class SoundexEncoding : public testing::Test {
public:
    Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
   
    auto encoded = soundex.Encode("A");
    ASSERT_THAT(encoded, Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits){

    auto encoded = soundex.Encode("I");
    ASSERT_THAT(encoded, Eq("I000"));
}