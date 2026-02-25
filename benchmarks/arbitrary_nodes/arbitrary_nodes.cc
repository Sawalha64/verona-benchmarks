// Copyright Microsoft and Project Verona Contributors.
// SPDX-License-Identifier: MIT
#include "arbitrary_nodes.h"

#include "region/region_base.h"

#include <benchmarker/benchmark_main.h>
#include <debug/harness.h>
#include <test/opt.h>
#include <gc_benchmark.h>

using namespace verona::rt::api;

#if defined(_WIN32) || defined(_WIN64)
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT
#endif

extern "C" EXPORT int run_benchmark(RegionType rt, int argc, char** argv)
{
  opt::Opt opt(argc, argv);

  // Default values
  int size = 1010;
  int regions = 100;
  bool enable_log = true;

  // Parse command line arguments
  if (argc >= 3)
  {
    size = std::atoi(argv[1]);
    regions = std::atoi(argv[2]);
  }

  if (argc >= 4)
  {
    std::string log_arg = argv[3];
    if (log_arg == "log")
    {
      enable_log = true;
    }
  }
  run_test_with_region(rt, [&]<RegionType R>() {
    return arbitrary_nodes::run_test<R>(size, regions);
  });
  return 0;
}