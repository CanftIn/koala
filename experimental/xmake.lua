add_packages("gtest")

target("switch_test")
    set_kind("binary")
    add_files("test/switch_test.cc")

add_includedirs("incubate")
target("static_string_test")
    set_kind("binary")
    add_files("test/static_string_test.cc")

target("bind_first_test")
    set_kind("binary")
    add_files("test/bind_first_test.cc")