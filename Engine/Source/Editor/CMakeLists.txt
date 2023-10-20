if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

project(LaunchApp)
add_compile_definitions(BR_PLATFORM_WINDOWS)
add_executable(LaunchApp_Start "Launch/Launch.cpp")

install(TARGETS LaunchApp_Start DESTINATION ${CMAKE_SOURCE_DIR}/lib)

#附加包含目录
target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/spdlog/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/imgui)
include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glm)
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glfw/include)
#include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glad/include)


#附加库目录
#target_link_directories(LaunchApp_Start PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/glfw/src)

#附加依赖项
target_link_libraries(LaunchApp_Start PRIVATE DllExport)

target_link_options(LaunchApp_Start PRIVATE /NODEFAULTLIB:MSVCRT.lib)




# 设置MT/MTd
set_property(TARGET LaunchApp_Start PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")
