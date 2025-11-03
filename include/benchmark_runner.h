#ifndef HOMEWORK_1_BENCHMARK_RUNNER_H
#define HOMEWORK_1_BENCHMARK_RUNNER_H

#include <vector>
#include <string>
#include "student.h"

// Запустити бенчмарки для всіх реалізованих варіантів структури даних та записати результати у CSV
void run_all_benchmarks(const std::vector<int> &sizes, int duration_sec, const std::string &out_csv);
// Запустити бенчмарки сортування: кількість повторів на розмір, запис у CSV (algorithm,size,run,time_ms,mem_bytes)
void run_sorting_bench(const std::vector<int> &sizes, int repeats, const std::string &out_csv);

#endif // HOMEWORK_1_BENCHMARK_RUNNER_H
