
#include <iostream>
#include <string>

#include "switch.hpp"

int main( int argc, char ** argv )
{
  using SwitchType = Switch<int, void(std::string)>;
  SwitchType switch_t = SwitchType(
    SwitchType::Case( 1, []( std::string str ) { std::cout << "Case 1: " << str << "\n"; } ),
    SwitchType::Case( 2, []( std::string str ) { std::cout << "Case 2: " << str << "\n"; } ),
    SwitchType::Case( 3, []( std::string str ) { std::cout << "Case 3: " << str << "\n"; } ),
    SwitchType::Case( 4, []( std::string str ) { std::cout << "Case 4: " << str << "\n"; } ),
    SwitchType::Default( []( std::string str ) { std::cout << "Unknown case: " << str << "\n"; } )
  );
  switch_t( 3, "Hello Switch!" );
};