set_project("Json")
set_languages("c++17")
set_warnings("all", "error")

add_rules("mode.debug", "mode.release")

add_includedirs("./include")

target("koala")
    set_kind("binary")
    add_files("src/*.cc")
