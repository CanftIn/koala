target("typeinfo_test")
    add_files("type_info_test.cc")
    add_deps("koala")
    add_packages("gtest")

target("define_test")
    add_files("define_test.cc")
    add_deps("koala")
    add_packages("gtest")

target("boxed_value_test")
    add_files("boxed_value_test.cc")
    add_deps("koala")
    add_packages("gtest")

target("boxed_number_test")
    add_files("boxed_number_test.cc")
    add_deps("koala")
    add_packages("gtest")