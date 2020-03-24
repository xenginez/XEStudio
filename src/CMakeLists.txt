# CMakeList.txt: XEStudio 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.12)

FILE(GLOB_RECURSE SRC_FILES *.cpp *.qrc *.ui)
add_library(XEStudio SHARED ${SRC_FILES})

target_link_libraries(XEStudio PRIVATE Qt5::Widgets Qt5::Sql XE)

target_compile_definitions(XEStudio PRIVATE XESTUDIO_LIBRARY)


FILE(GLOB LIBRARY_FILES ../depend/bin/${XE_PLATFORM_PATH}/${XE_CONFIG}/*.*)
foreach (LIBRARY_FILE ${LIBRARY_FILES})
	add_custom_command(TARGET XEStudio
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_FILE} "${XE_PLATFORM_PATH}/target/${XE_CONFIG}/bin"
			)
endforeach (LIBRARY_FILE)
