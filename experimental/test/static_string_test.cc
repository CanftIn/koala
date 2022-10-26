#include <iostream>
#include <typeinfo>
#include <string>
#include <gtest/gtest.h>

#include "./incubate/static_string_v1.hpp"
#include "./incubate/static_string_v2.hpp"

TEST(StaticString_v1, base) {
  std::string str = "test";
  StaticString st_str("test");
  EXPECT_NE(st_str.c_str(), str.c_str());
  EXPECT_EQ(st_str == str, true);
}

TEST(StaticString_v2, base) {
  using namespace v2;
  EXPECT_EQ("Hello"_ss, "Hello");
  EXPECT_NE("World"_ss, "world");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}