if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

project(Core CXX)

#生成dll库文件
file(GLOB_RECURSE RSOURCES "./*.cpp" "./*.h")
add_library(DllExport SHARED ${RSOURCES})

#设置头文件索引
target_include_directories(DllExport PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 设置MT/MTd
set_property(TARGET DllExport PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")

#附加包含目录
target_include_directories(DllExport PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/spdlog/include)
target_include_directories(DllExport PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glfw/include)
include_directories()
include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/imgui)


#附加库目录
target_link_directories(DllExport PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/spdlog)
target_link_directories(DllExport PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/glfw/src)
message(status " BinDIr : ${CMAKE_SOURCE_DIR}")
#附加依赖项
target_link_libraries(DllExport PRIVATE glfw3)
target_link_libraries(DllExport PRIVATE spdlog)
target_link_libraries(DllExport PRIVATE OpenGL32)
target_link_libraries(DllExport PRIVATE ImguiLibExport)


add_compile_definitions(BR_PLATFORM_WINDOWS)
add_compile_definitions(BR_BUILD_DLL)

#安装到指定文件夹
install(TARGETS DllExport DESTINATION ${CMAKE_SOURCE_DIR}/lib)

#设置预编译头
target_precompile_headers(DllExport PUBLIC PrecComPile/PreComHead.h)


