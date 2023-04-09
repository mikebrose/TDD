#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Soundex.hpp"
#include <string>

using ::testing::Return;
using ::testing::NiceMock;

TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
    Soundex soundex;
    std::string result = soundex.Encode("b");
    EXPECT_EQ(result, "b");
}

