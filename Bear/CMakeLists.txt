cmake_minimum_required(VERSION 3.2)
project(DLLTest)

add_subdirectory(src)
set(SOURCE_FILES main.cpp)

add_executable(DLLTest_Start ${SOURCE_FILES})


#target_link_directories(divider PRIVATE ${CMAKE_SOURCE_DIR}/lib)

#头文件依赖
target_include_directories(DLLTest_Start PRIVATE ./)

#依赖库目录
target_link_directories(DLLTest_Start PRIVATE ${PROJECT_BINARY_DIR}/src)

#依赖项
target_link_libraries(DLLTest_Start PRIVATE DllExport)

#安装到指定文件
install(TARGETS DLLTest_Start DESTINATION ${CMAKE_SOURCE_DIR}/lib)