project(test)
add_compile_definitions(BR_PLATFORM_WINDOWS)


add_executable(App_Start src/HiveAPP.cpp)

install(TARGETS App_Start DESTINATION ${CMAKE_SOURCE_DIR}/lib)

#target_link_directories(App_Start PRIVATE ${CMAKE_SOURCE_DIR}/lib)


#find spdlog 库
find_library(FIND_spdlogd_LIB_DIR spdlogd HINTS ${CMAKE_BINARY_DIR}/Dep)
find_library(FIND_glfw_LIB_DIR glfw3 HINTS ${CMAKE_BINARY_DIR}/Dep)

#附加包含目录
target_include_directories(App_Start PRIVATE ${CMAKE_SOURCE_DIR}/Dep/spdlog/include)
include_directories(${CMAKE_SOURCE_DIR}/Dep/spdlog/include)
include_directories(${CMAKE_SOURCE_DIR}/Dep/glfw/include)

#附加库目录
target_link_directories(App_Start PRIVATE ${FIND_spdlogd_LIB_DIR})
link_directories(${FIND_spdlogd_LIB_DIR})
link_directories(${FIND_glfw_LIB_DIR})

#附加依赖项
target_link_libraries(App_Start PRIVATE DllExport)
target_link_libraries(App_Start PRIVATE spdlog)
link_libraries(spdlog)
link_libraries(DllExport)
link_libraries(glfw3)