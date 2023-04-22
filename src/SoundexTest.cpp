#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Soundex.hpp"
#include <string>
#include <iostream>

using testing::Eq;
using testing::StartsWith;

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

TEST_F(SoundexEncoding, IgnoresNonAlphabeticCharsButContinues){
    ASSERT_THAT(soundex.Encode("A#c"), Eq("A200"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters){
    ASSERT_THAT(soundex.Encode("Dcdlb").length(), Eq(4U));
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters){
    ASSERT_THAT(soundex.Encode("Baeiouhycdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings){
    ASSERT_THAT(soundex.EncodeDigit('b'), Eq(soundex.EncodeDigit('f')));
    ASSERT_THAT(soundex.EncodeDigit('c'), Eq(soundex.EncodeDigit('g')));
    ASSERT_THAT(soundex.EncodeDigit('d'), Eq(soundex.EncodeDigit('t')));

    ASSERT_THAT(soundex.Encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncoding, UppercasesFirstLetter){
    ASSERT_THAT(soundex.Encode("abcd"), StartsWith("A"));
}

TEST_F(SoundexEncoding, RemainsUppercasedFirstLetter){
    ASSERT_THAT(soundex.Encode("Abcd"), StartsWith("A"));
}