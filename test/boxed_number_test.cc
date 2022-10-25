#include <iostream>
#include <typeinfo>
#include <vector>
#include <gtest/gtest.h>

#include "koala/boxed_value.hpp"

using namespace koala;

TEST(BoxedValue, string) {

}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}