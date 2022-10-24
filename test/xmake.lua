target("typeinfo_test")
    add_files("type_info_test.cc")
    add_deps("koala")
    add_packages("gtest")