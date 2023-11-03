if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

project(BearEditor)
add_compile_definitions(BR_PLATFORM_WINDOWS)

file(GLOB_RECURSE RSOURCES "Editor/*.cpp" "Editor/*.h")
add_executable(BearEditor ${RSOURCES})

#install(TARGETS LaunchApp_Start DESTINATION ${CMAKE_SOURCE_DIR}/lib)

#附加包含目录
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/spdlog/include)
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glfw/include)
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glad/include)
target_include_directories(BearEditor PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/spdlog/include)
target_include_directories(BearEditor PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glfw/include)
target_include_directories(BearEditor PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glad/include)
target_include_directories(BearEditor PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/imgui)
target_include_directories(BearEditor PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glm)
target_include_directories(BearEditor PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Source/Runtime)


target_link_directories(BearEditor PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/spdlog)
target_link_directories(BearEditor PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/glfw/src)
target_link_directories(BearEditor PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/imgui)
target_link_directories(BearEditor PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/glad)
target_link_directories(BearEditor PRIVATE ${CMAKE_BINARY_DIR}/Engine/Source/Runtime)



target_link_libraries(BearEditor PRIVATE DllExport)
target_link_libraries(BearEditor PRIVATE opengl32)
target_link_libraries(BearEditor PRIVATE spdlog)
target_link_libraries(BearEditor PRIVATE glfw3)
target_link_libraries(BearEditor PRIVATE glad)

target_link_options(BearEditor PRIVATE /NODEFAULTLIB:MSVCRT.lib)






#project(LaunchApp)
#
#add_compile_definitions(BR_PLATFORM_WINDOWS)
#add_executable(LaunchApp_Start "Launch/Launch.cpp")
#
#
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/spdlog/include)
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glfw/include)
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glad/include)
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/imgui)
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glm)
#target_include_directories(LaunchApp_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Source/Runtime)
#
#
###附加库目录
#target_link_directories(LaunchApp_Start PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/spdlog)
#target_link_directories(LaunchApp_Start PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/glfw/src)
#target_link_directories(LaunchApp_Start PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/imgui)
#target_link_directories(LaunchApp_Start PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/glad)
#target_link_directories(LaunchApp_Start PRIVATE ${CMAKE_BINARY_DIR}/Engine/Source/Runtime)
#
#
#
#target_link_libraries(LaunchApp_Start PRIVATE DllExport)
#target_link_libraries(LaunchApp_Start PRIVATE opengl32)
#target_link_libraries(LaunchApp_Start PRIVATE spdlog)
#target_link_libraries(LaunchApp_Start PRIVATE glfw3)
#target_link_libraries(LaunchApp_Start PRIVATE glad)
#
#
#target_link_options(LaunchApp_Start PRIVATE /NODEFAULTLIB:MSVCRT.lib)
#
#
#
#
## 设置MT/MTd
#set_property(TARGET LaunchApp_Start PROPERTY
#  MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")
#