#ifndef KOALA_KOALA_IMPL_HPP__
#define KOALA_KOALA_IMPL_HPP__

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <typeinfo>
#include <utility>
#include <vector>

#include "type_info.hpp"

namespace koala
{
  
  class Module {
   public:
    Module& add(TypeInfo ti, std::string name) {
      _typeinfos.emplace_back(ti, std::move(name));
      return *this;
    }

   private:
    std::vector<std::pair<TypeInfo, std::string>> _typeinfos;
  };
} // namespace koala

#endif
