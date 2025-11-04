#!/usr/bin/env bash
set -e


echo "Configuring build (out-of-source to ./build)..."
cmake -S . -B build

echo "Building project..."
cmake --build build -- -j 4

echo "Running benchmarks..."
./bin/run_all

echo "Done. Results are in bench_results/"
