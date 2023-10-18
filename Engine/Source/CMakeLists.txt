cmake_minimum_required(VERSION 3.2)
project(CoreDllTest)

add_subdirectory(Editor)
add_subdirectory(Renderer)
add_subdirectory(Runtime)


#set(SOURCE_FILES CoreDllTest.cpp)

#add_executable(CoreDllTest_Start ${SOURCE_FILES})

#头文件依赖
#target_include_directories(CoreDllTest_Start PRIVATE ./)

#依赖库目录
#target_link_directories(CoreDllTest_Start PRIVATE ${PROJECT_BINARY_DIR}/src)

#依赖项
#target_link_libraries(CoreDllTest_Start PRIVATE DllExport)

#安装到指定文件
#install(TARGETS CoreDllTest_Start DESTINATION ${CMAKE_SOURCE_DIR}/lib)
