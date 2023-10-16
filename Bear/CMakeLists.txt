cmake_minimum_required(VERSION 3.2)
project(divider)

add_subdirectory(src)
set(SOURCE_FILES main.cpp)

add_executable(divider ${SOURCE_FILES})


#target_link_directories(divider PRIVATE ${CMAKE_SOURCE_DIR}/lib)

#头文件依赖
target_include_directories(divider PRIVATE ./)

#依赖库目录
target_link_directories(divider PRIVATE ${PROJECT_BINARY_DIR}/src)

set(LIBB_DIR D:/Engine/BeEngine/out/build/x64-debug/Dep/spdlog)
find_library(FF_LIB_DIR DllExport HINTS ${PROJECT_BINARY_DIR}/src)
message(status " FindLIB : ${F_LIB_DIR}")

#依赖项
target_link_libraries(divider PRIVATE DllExport)

install(TARGETS divider DESTINATION ${CMAKE_SOURCE_DIR}/lib)