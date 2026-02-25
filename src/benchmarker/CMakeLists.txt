add_executable(benchmarker
    benchmark_main.cc
)

target_include_directories(benchmarker 
    PRIVATE ${VERONA_RT_PATH}/test
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(benchmarker
    PRIVATE verona_rt
    PRIVATE ${CMAKE_DL_LIBS}
)

target_compile_features(benchmarker PRIVATE cxx_std_17)
