set_project("Json")
set_languages("c++17")
set_warnings("all", "error")

add_rules("mode.debug", "mode.release")

add_includedirs("./include")

add_requires("gtest")

target("koala")
    set_kind("binary")
    add_files("src/*.cc")

-- target("koala_test")
--     set_kind("binary")
--     add_files("test/*.cc")

target("koala_experimental")
    set_kind("binary")
    add_includedirs("./experimental")
    add_files("experimental/*.cc")

add_subdirs('test')
