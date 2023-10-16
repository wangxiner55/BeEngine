project(Bear CXX)

#add_definitions(BR_PLATFORM_WINDOWS BR_BUILD_DLL)
add_compile_definitions(BR_PLATFORM_WINDOWS BR_BUILD_DLL)


file(GLOB_RECURSE RSOURCES "Bear/*.cpp")
add_library(DllExport SHARED ${RSOURCES} CPrint.cpp)

#设置头文件索引
target_include_directories(DllExport PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


#导入新的dll或lib需要做的
find_library(FIND_LIB_DIR spdlogd HINTS ${CMAKE_BINARY_DIR}/Dep/spdlog)
message(STATUS " FInd : ${FIND_LIB_DIR}")

#附加包含目录
target_include_directories(DllExport PRIVATE ${CMAKE_SOURCE_DIR}/Dep/spdlog/include)

#附加库目录
target_link_directories(DllExport PRIVATE ${FIND_LIB_DIR})

#附加依赖项
target_link_libraries(DllExport PRIVATE spdlog)


#安装到指定文件夹
install(TARGETS DllExport DESTINATION ${CMAKE_SOURCE_DIR}/lib)