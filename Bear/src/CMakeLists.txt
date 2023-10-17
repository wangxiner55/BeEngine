project(Bear CXX)

#add_definitions(BR_PLATFORM_WINDOWS BR_BUILD_DLL)
add_compile_definitions(BR_PLATFORM_WINDOWS)
add_compile_definitions(BR_BUILD_DLL)


#����dll���ļ�
file(GLOB_RECURSE RSOURCES "./*.cpp" )
add_library(DllExport SHARED ${RSOURCES} "_CPrint.cpp" Bear.h "PreComHead.h")


#����ͷ�ļ�����
target_include_directories(DllExport PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#find spdlog glfw ��
find_library(FIND_spdlog_LIB_DIR spdlogd HINTS ${CMAKE_BINARY_DIR}/Dep)
find_library(FIND_glfw_LIB_DIR glfw3 HINTS ${CMAKE_BINARY_DIR}/Dep)

#���Ӱ���Ŀ¼
target_include_directories(DllExport PRIVATE ${CMAKE_SOURCE_DIR}/Dep/spdlog/include)
target_include_directories(DllExport PRIVATE ${CMAKE_SOURCE_DIR}/Dep/glfw/include)

#���ӿ�Ŀ¼
target_link_directories(DllExport PRIVATE ${CMAKE_BINARY_DIR}/Dep/spdlog)
target_link_directories(DllExport PRIVATE ${CMAKE_BINARY_DIR}/Dep/glfw/src)

#����������
target_link_libraries(DllExport PRIVATE glfw3)
target_link_libraries(DllExport PRIVATE spdlog)
target_link_libraries(DllExport PRIVATE OpenGL32)

#��װ��ָ���ļ���
install(TARGETS DllExport DESTINATION ${CMAKE_SOURCE_DIR}/lib)

#����Ԥ����ͷ
target_precompile_headers(DllExport PUBLIC PreComHead.h)