# Benchmark tests as shared libraries

function(add_benchmark_test name)
  add_library(benchmark-${name} SHARED ${ARGN})
  set_target_properties(benchmark-${name} PROPERTIES PREFIX "lib")
  set_target_properties(benchmark-${name} PROPERTIES OUTPUT_NAME "benchmark-${name}")
  target_include_directories(benchmark-${name} PRIVATE ${CMAKE_SOURCE_DIR}/src)
  target_compile_features(benchmark-${name} PRIVATE cxx_std_17)
  target_link_libraries(benchmark-${name} PRIVATE verona_rt atomic)
endfunction()

# Automatically add all benchmarks from subdirectories
file(GLOB BENCHMARK_DIRS LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
foreach(BENCH_DIR ${BENCHMARK_DIRS})
  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${BENCH_DIR})
    # Find any .cc file in the directory
    file(GLOB BENCH_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/${BENCH_DIR}/*.cc)
    if(BENCH_SOURCE)
      list(GET BENCH_SOURCE 0 FIRST_SOURCE)
      file(RELATIVE_PATH REL_SOURCE ${CMAKE_CURRENT_SOURCE_DIR} ${FIRST_SOURCE})
      add_benchmark_test(${BENCH_DIR} ${REL_SOURCE})
    endif()
  endif()
endforeach()
