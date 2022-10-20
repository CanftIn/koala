set_project("Json")
set_languages("c++11")
set_warnings("all", "error")

add_rules("mode.debug", "mode.release")

add_includedirs("./")

target("koala")
    set_kind("binary")
    add_files("src/*.cc")
