#include <iostream>
#include <typeinfo>
#include <string>
#include <gtest/gtest.h>

#include "./incubate/static_string.hpp"

TEST(StaticString, base) {
  std::string str = "test";
  StaticString st_str("test");
  EXPECT_NE(st_str.c_str(), str.c_str());
  EXPECT_EQ(st_str == str, true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}