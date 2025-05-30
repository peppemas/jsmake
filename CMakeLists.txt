cmake_minimum_required(VERSION 3.20)

project(jsmake)
enable_language(CXX)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(BUILD_SHARED_LIBS OFF)
if (NOT APPLE)
SET(CMAKE_EXE_LINKER_FLAGS "-static")
endif()
SET(CMAKE_GENERATOR_TOOLSET "x64")

if(WIN32)
  set(PLATFORM windows)
else()
  set(PLATFORM posix)
endif()

set(CMAKE_C_FLAGS "-D IW_64")

# Add linker flags to resolve image base issue
if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
endif()

# Explicitly set architecture
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")

# Add the -Wattributes flag to the compiler options
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wattributes)
endif()

if(MSVC)
  add_compile_options(/permissive- /utf-8 /Zc:__cplusplus)
  add_definitions(-DNOMINMAX)
endif()

set(DUKTAPE_SOURCE "third_parties/duktape-2.6.0/src/*.c")
set(DUKTAPE_HEADERS "third_parties/duktape-2.6.0/src/*.h")

set(DUKTAPE_CPP_SOURCE "third_parties/duktape-cpp/duktape-cpp/*.cpp" "third_parties/duktape-cpp/duktape-cpp/*.inl")
set(DUKTAPE_CPP_HEADERS "third_parties/duktape-cpp/duktape-cpp/*.h")

set(CUTE_HEADERS "third_parties/cute_headers/*.h")

set(REPROC_SOURCE 
  "third_parties/reproc/src/clock.${PLATFORM}.c"
  "third_parties/reproc/src/drain.c"
  "third_parties/reproc/src/error.${PLATFORM}.c"
  "third_parties/reproc/src/handle.${PLATFORM}.c"
  "third_parties/reproc/src/init.${PLATFORM}.c"
  "third_parties/reproc/src/options.c"
  "third_parties/reproc/src/pipe.${PLATFORM}.c"
  "third_parties/reproc/src/process.${PLATFORM}.c"
  "third_parties/reproc/src/redirect.${PLATFORM}.c"
  "third_parties/reproc/src/redirect.c"
  "third_parties/reproc/src/reproc.c"
  "third_parties/reproc/src/run.c"
  "third_parties/reproc/src/utf.${PLATFORM}.c"
)
set(REPROC_HEADERS "third_parties/reproc/include/reproc/*.h")

set(ARGPARSE_SOURCE "third_parties/argparse-master/argparse.c")
set(LINENOISE_NG_SOURCE "third_parties/linenoise-ng/src/*.cpp")

file(GLOB_RECURSE source_files "src/*.cpp"
            ${DUKTAPE_SOURCE}
            ${DUKTAPE_CPP_SOURCE}
            ${REPROC_SOURCE}
            ${ARGPARSE_SOURCE}
            ${LINENOISE_NG_SOURCE}
          )
file(GLOB_RECURSE header_files "src/*.h")

include_directories(src)
include_directories(third_parties/duktape-2.6.0/src)
include_directories(third_parties/duktape-cpp)
include_directories(third_parties/reproc/include)
include_directories(third_parties/inja)
include_directories(third_parties/cute_headers)
include_directories(third_parties/argparse-master)
include_directories(third_parties/termcolor/include)
include_directories(third_parties/linenoise-ng/include)
include_directories(third_parties/cpp-httplib-0.20.0)

add_executable(${PROJECT_NAME} ${source_files} ${header_files} ${inl_files})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

target_compile_definitions(jsmake PRIVATE WIN32_LEAN_AND_MEAN)

if (WIN32)
target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif()
