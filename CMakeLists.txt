cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0054 NEW)

project(koala)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# required since cmake 3.4 at least for libc++
set(CMAKE_ENABLE_EXPORTS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT MINGW)
  find_library(READLINE_LIBRARY NAMES readline PATH /usr/lib /usr/local/lib /opt/local/lib)
endif()

if(UNIX AND NOT APPLE)
  find_program(VALGRIND NAMES valgrind PATH /usr/bin /usr/local/bin)
endif()

enable_testing()

message(STATUS "Detecting readline support")
if(READLINE_LIBRARY)
  message(STATUS "Found: ${READLINE_LIBRARY}")
  set(READLINE_LIB readline)
  add_definitions(/DREADLINE_AVAILABLE)
else()
  message(STATUS "Not Found")
  set(READLINE_LIB)
  set(READLINE_FLAG)
endif()

include_directories(include)
include_directories(experimental)

set(KOALA_HEADERS
  include/koala.hpp
  include/koala/bind_first.hpp
  include/koala/bootstrap.hpp
  include/koala/boxed_cast.hpp
  include/koala/boxed_number.hpp
  include/koala/callable_traits.hpp
  include/koala/cpplisp.hpp
  include/koala/define.hpp
  include/koala/exception.hpp
  include/koala/function_call.hpp
  include/koala/function_params.hpp
  include/koala/function_signature.hpp
  include/koala/handle_return.hpp
  include/koala/koala_algebraic.hpp
  include/koala/koala_common.hpp
  include/koala/koala_engine.hpp
  include/koala/koala_impl.hpp
  include/koala/koala_stdlib.hpp
  include/koala/proxy_function.hpp
  include/koala/register_function.hpp
  include/koala/type_conversions.hpp
  include/koala/type_info.hpp
  include/koala/type_trait.hpp
  include/koala/utility.hpp
  experimental/no_destructor.hpp
)

set_source_files_properties($KOALA_HEADERS} PROPERTIES HEADER_FILE_ONLY TRUE)

list(APPEND LIBS ${READLINE_LIB})

add_executable(koala src/koala.cc ${KOALA_HEADERS})
target_link_libraries(koala ${LIBS})

add_library(koalascript INTERFACE)
target_include_directories(koalascript INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)