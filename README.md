
# Verona Benchmarks

GC benchmarking suite for the Verona runtime.

## Getting Started

### 1. Directory Structure

Both repositories must be in the same parent directory:

```
parent/
├── verona-rt-gc-bench/
└── verona-benchmarks/
```

### 2. Build Verona Runtime

Build verona-rt-gc-bench according to its specification.

### 3. Build Verona Benchmarks

```bash
cd verona-benchmarks
mkdir -p build_ninja
cd build_ninja
cmake .. -GNinja -DCMAKE_BUILD_TYPE=Debug
ninja
```

*Custom verona-rt path:*

```bash
cmake .. -GNinja -DVERONA_RT_PATH=/path/to/verona-rt-gc-bench
ninja
```

### 4. Run Benchmarks

```bash
cd build_ninja
Usage: ./src/benchmarker/benchmarker --runs <n> --warmup_runs <n> <path_to_so> [args...]
```