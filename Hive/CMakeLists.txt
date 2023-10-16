project(test)
add_compile_definitions(BR_PLATFORM_WINDOWS)


add_executable(App_Start src/HiveAPP.cpp)

install(TARGETS App_Start DESTINATION ${CMAKE_SOURCE_DIR}/lib)

#target_link_directories(App_Start PRIVATE ${CMAKE_SOURCE_DIR}/lib)

#导入新的dll或lib需要做的
find_library(FIND_LIB_DIR spdlogd HINTS ${CMAKE_BINARY_DIR}/Dep/spdlog)
message(STATUS " FInd : ${FIND_LIB_DIR}")

#附加包含目录
target_include_directories(App_Start PRIVATE ${CMAKE_SOURCE_DIR}/Dep/spdlog/include)

#附加库目录
target_link_directories(App_Start PRIVATE ${FIND_LIB_DIR})

#附加依赖项
target_link_libraries(App_Start PRIVATE DllExport)
target_link_libraries(App_Start PRIVATE spdlog)