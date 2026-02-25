cmake_minimum_required(VERSION 3.10)
project(verona-benchmarks CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find verona-rt (assumes it's built and available)
set(VERONA_RT_PATH "${CMAKE_SOURCE_DIR}/../verona-rt-gc-bench" CACHE PATH "Path to verona-rt")

if(NOT EXISTS "${VERONA_RT_PATH}/src/rt/verona.h")
  message(FATAL_ERROR "Could not find verona-rt at ${VERONA_RT_PATH}")
endif()

# Create a local verona_rt interface library that matches the original
# This allows the benchmarker to be compiled with the same flags
add_library(verona_rt INTERFACE)

# Add necessary compiler flags and defines (from verona-rt)
target_compile_options(verona_rt INTERFACE -mcx16)
target_compile_definitions(verona_rt INTERFACE
  MALLOC_USABLE_SIZE_QUALIFIER=const
  SNMALLOC_BACKTRACE_HEADER="execinfo.h"
  SNMALLOC_CHEAP_CHECKS
  SNMALLOC_HAS_LINUX_FUTEX_H
  SNMALLOC_HAS_LINUX_RANDOM_H
  SNMALLOC_NO_REALLOCARR
  SNMALLOC_NO_REALLOCARRAY
  SNMALLOC_PLATFORM_HAS_GETENTROPY
  SNMALLOC_PTHREAD_ATFORK_WORKS
  SNMALLOC_USE_WAIT_ON_ADDRESS=1
)

if(UNIX AND NOT APPLE)
  target_compile_options(verona_rt INTERFACE -pthread)
  target_link_libraries(verona_rt INTERFACE -pthread)
target_link_libraries(verona_rt INTERFACE -rdynamic)
endif()

# Include verona-rt headers
target_include_directories(verona_rt INTERFACE
  ${VERONA_RT_PATH}/src/rt
  ${VERONA_RT_PATH}/build_ninja/_deps/snmalloc-src/src
)

# Link against snmalloc (header-only access from build directory)
target_link_directories(verona_rt INTERFACE ${VERONA_RT_PATH}/build_ninja/src/rt)

# Add subdirectories
add_subdirectory(src/benchmarker)
add_subdirectory(benchmarks)
