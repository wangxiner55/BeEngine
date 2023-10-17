# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (Engine)

#包含子项目。
add_subdirectory(Bear)
add_subdirectory(Hive)
add_subdirectory(Dep/spdlog)
add_subdirectory(Dep/glfw)


#设置路径别名
set(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})  
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)
set(BIN_DIR		${CMAKE_SOURCE_DIR}/bin)
set(LIB_DIR		${CMAKE_SOURCE_DIR}/lib)
set(DEP_DIR		${CMAKE_BINARY_DIR}/Dep)
