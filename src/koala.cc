#include <iostream>

#include "koala.hpp"

using namespace koala;

int main(int argc, char** argv) {
    std::cout << "koala version: " << BuildInfo::version() << std::endl;
    return 0;
}
