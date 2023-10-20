#if (POLICY CMP0091)
#  cmake_policy(SET CMP0091 NEW)
#endif (POLICY CMP0091)

project(Core CXX)

#生成dll库文件
file(GLOB_RECURSE RSOURCES "./*.cpp" "./*.h")
add_library(DllExport SHARED ${RSOURCES})


#设置头文件索引
target_include_directories(DllExport PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


#附加包含目录
target_include_directories(DllExport PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/spdlog/include)
target_include_directories(DllExport PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/imgui)
include_directories(${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glm)


#附加库目录
target_link_directories(DllExport PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/spdlog)
target_link_directories(DllExport PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/glfw/src)
target_link_directories(DllExport PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/imgui)

#附加依赖项
#target_link_libraries(DllExport PRIVATE legacy_stdio_definitions)
target_link_libraries(DllExport PRIVATE GUIExport)
target_link_libraries(DllExport PRIVATE opengl32)
target_link_libraries(DllExport PRIVATE glfw3)
target_link_libraries(DllExport PRIVATE spdlog)

#target_link_options(DllExport PRIVATE /NODEFAULTLIB:MSVCRT.lib)

#预编译宏
add_compile_definitions(BR_PLATFORM_WINDOWS)
add_compile_definitions(BR_BUILD_DLL)

#忽略编译文件
target_link_options(DllExport PRIVATE /NODEFAULTLIB:MSVCRT.lib)

#安装到指定文件夹
install(TARGETS DllExport DESTINATION ${CMAKE_SOURCE_DIR}/lib)

#设置预编译头
target_precompile_headers(DllExport PUBLIC PrecComPile/PreComHead.h)

# 设置MT/MTd
set_property(TARGET DllExport PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")







#  Imgui Test Modeule , We Need move to A New File Context
add_executable(Imgui_Start "Platform/OpenGL/main.cpp" "Platform/OpenGL/imgui_impl_opengl3_loader.h" "Platform/OpenGL/imgui_impl_glfw.h" "Platform/OpenGL/imgui_impl_glfw.cpp" "Platform/OpenGL/ImGuiOpenGlRenderer.h" "Platform/OpenGL/ImGuiOpenGlRenderer.cpp")


#target_include_directories(Imgui_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/glfw/include)
target_include_directories(Imgui_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/imgui/examples/libs/glfw/include)
target_include_directories(Imgui_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/imgui)

target_link_directories(Imgui_Start PRIVATE ${CMAKE_SOURCE_DIR}/Engine/Binaries/ThirdParty/imgui/examples/libs/glfw/lib-vc2010-64)
#target_link_directories(Imgui_Start PRIVATE ${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/glfw/src)
link_directories(${CMAKE_BINARY_DIR}/Engine/Binaries/ThirdParty/imgui)



target_link_libraries(Imgui_Start PRIVATE GUIExport)
target_link_libraries(Imgui_Start PRIVATE opengl32)
target_link_libraries(Imgui_Start PRIVATE glfw3)


target_link_options(Imgui_Start PRIVATE /NODEFAULTLIB:MSVCRT.lib)