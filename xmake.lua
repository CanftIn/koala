set_project("koala-lang")
set_languages("c++17")
set_warnings("allextra")
--set_warnings("all", "error")

-- set_config("cxxflags", "-Wno-attributes")
set_config("cc", "clang")
set_config("cxx", "clang++")
set_config("ld", "clang++")

add_rules("mode.debug", "mode.release")

add_includedirs("./include")
add_includedirs("./experimental")

add_requires("gtest")

target("koala")
    set_kind("binary")
    add_files("src/*.cc")

-- target("koala_test")
--     set_kind("binary")
--     add_files("test/*.cc")

add_subdirs('test')
add_subdirs('unittests')
add_subdirs('experimental')