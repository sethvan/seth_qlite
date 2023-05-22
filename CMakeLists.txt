cmake_minimum_required(VERSION 3.16)

project( seth_qlite LANGUAGES "CXX" )

add_executable( seth_qlite 
src/seth_qlite.cpp
src/test.cpp )

find_library(SQLITE3_LIBRARY sqlite3)
target_link_libraries(seth_qlite PRIVATE ${SQLITE3_LIBRARY})

target_include_directories( seth_qlite PRIVATE include )
target_compile_features( seth_qlite PRIVATE cxx_std_20)
