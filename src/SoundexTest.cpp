#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Soundex.hpp"
#include <string>

using testing::Eq;

TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
    Soundex soundex;
    auto encoded = soundex.Encode("A");
    ASSERT_THAT(encoded, Eq("A"));
}

 