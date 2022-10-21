#include <iostream>
#include <typeinfo>

#include "koala/type_info.hpp"
 
struct Base { virtual ~Base() = default; };
struct Derived : Base {};

template<typename U, typename V> constexpr bool same = std::is_same_v<U, V>;
 
void BareType_Test() {
  using namespace koala::detail;
	Base b1;
	Derived d1;
 
	const Base *pb = &b1;
	std::cout << typeid(*pb).name() << '\n';
	pb = &d1;
	std::cout << typeid(*pb).name() << '\n';

  std::cout << typeid(koala::detail::BareType<const Base*>::type).name() << '\n';
  std::cout << typeid(const Base*).name() << '\n';

  static_assert(
        same< BareType_t< int >, int >
    and same< BareType_t< const int >, int >
    and same< BareType_t< volatile int >, int >
    and same< BareType_t< const volatile int >, int >
    and same< BareType_t< const volatile int* >, int >
    and same< BareType_t< const int* volatile >, int >
    and same< BareType_t< int* const volatile >, int >
  );
}

struct UnknownType {};

void TypeInfo_Test() {
  const std::type_info& unknowntype_info = typeid(UnknownType);
  std::cout << "unknowntype_info type: " << unknowntype_info.name() << "\n";

  if(typeid(Derived).before(typeid(Base)))
    std::cout << "Base goes before Derived in this implementation.\n";
  else
    std::cout << "Derived goes before Base in this implementation.\n";
}

int main() {
  BareType_Test();
  TypeInfo_Test();
}