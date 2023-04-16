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
    ASSERT_THAT(soundex.Encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabeticChars){
    ASSERT_THAT(soundex.Encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncoding, DISABLED_LimitsLengthToFourCharacters){
    ASSERT_THAT(soundex.Encode("Dcdlb").length(), Eq(4U));
}