cmake_minimum_required (VERSION 3.12)

project ("Editor")

FILE(GLOB_RECURSE SRC_FILES *.cpp *.qrc *.ui)
add_executable(Editor ${SRC_FILES})

target_link_libraries(Editor PRIVATE Qt5::Widgets Qt5::Sql XE XEStudio)
