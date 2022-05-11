cmake_minimum_required(VERSION 3.12)
set(PROJECT_NAME cpp_app)
project(${PROJECT_NAME} CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

include_directories(./include)
link_directories(./lib)

set(RES_FILES "")
if(MINGW)
 set(RES_FILES "res/Resource.rc")
 set(CMAKE_RC_COMPILER_INIT windres)
 ENABLE_LANGUAGE(RC)
 SET(CMAKE_RC_COMPILE_OBJECT
 "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")
endif(MINGW)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -DUNICODE")

file(GLOB sourcefiles "src/*.h" "src/*.cpp")
add_executable(${PROJECT_NAME} ${sourcefiles} ${RES_FILES})



