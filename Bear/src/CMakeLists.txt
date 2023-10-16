project(Bear CXX)

#add_definitions(BR_PLATFORM_WINDOWS BR_BUILD_DLL)
add_compile_definitions(BR_PLATFORM_WINDOWS BR_BUILD_DLL)


#生成dll库文件
file(GLOB_RECURSE RSOURCES "Bear/*.cpp")
add_library(DllExport SHARED ${RSOURCES} CPrint.cpp Bear.h "PreComHead.h")


#设置头文件索引
target_include_directories(DllExport PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#find spdlog glfw 库
find_library(FIND_spdlog_LIB_DIR spdlogd HINTS ${CMAKE_BINARY_DIR}/Dep)
find_library(FIND_glfw_LIB_DIR glfw3 HINTS ${CMAKE_BINARY_DIR}/Dep)
message(status " Find glfw : ${FIND_glfw_LIB_DIR}")

#附加包含目录
target_include_directories(DllExport PRIVATE ${CMAKE_SOURCE_DIR}/Dep/spdlog/include)
target_include_directories(DllExport PRIVATE ${CMAKE_SOURCE_DIR}/Dep/glfw/include)

#附加库目录
target_link_directories(DllExport PRIVATE ${FIND_spdlog_LIB_DIR})
target_link_directories(DllExport PRIVATE ${FIND_glfw_LIB_DIR})

#附加依赖项
target_link_libraries(DllExport PRIVATE glfw3)
target_link_libraries(DllExport PRIVATE spdlog)


#安装到指定文件夹
install(TARGETS DllExport DESTINATION ${CMAKE_SOURCE_DIR}/lib)

#设置预编译头
target_precompile_headers(DllExport PUBLIC PreComHead.h)