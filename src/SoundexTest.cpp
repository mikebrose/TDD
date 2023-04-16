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
   
    ASSERT_THAT(soundex.Encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits){

    ASSERT_THAT(soundex.Encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits){
    EXPECT_THAT(soundex.Encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabeticChars){
    EXPECT_THAT(soundex.Encode("A#"), Eq("A000"));
}