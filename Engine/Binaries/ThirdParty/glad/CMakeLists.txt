

project(glad)

file(GLOB_RECURSE RSOURCES "./*.c" "./*.h")
add_library(glad STATIC ${RSOURCES})


target_include_directories(glad  PUBLIC include)