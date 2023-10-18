if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)




project(LaunchApp)
add_compile_definitions(BR_PLATFORM_WINDOWS)
add_executable(LaunchApp_Start "Launch/Launch.cpp")

install(TARGETS LaunchApp_Start DESTINATION ${CMAKE_SOURCE_DIR}/lib)

# 设置MT/MTd
set_property(TARGET LaunchApp_Start PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")


#附加包含目录
target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/spdlog/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/imgui)
#include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/spdlog/include)
#include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glfw/include)

#附加库目录
#target_link_directories(LaunchApp_Start PRIVATE ${FIND_spdlogd_LIB_DIR})
#link_directories(${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/spdlog)
#link_directories(${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/glfw/src)



#附加依赖项
target_link_libraries(LaunchApp_Start PRIVATE DllExport)
target_link_libraries(LaunchApp_Start PRIVATE ImguiLibExport)
#target_link_libraries(LaunchApp_Start PRIVATE spdlog)
#link_libraries(spdlog)
#link_libraries(DllExport)
#link_libraries(glfw3)