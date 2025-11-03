#include "benchmark_runner.h"
#include <filesystem>
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    namespace fs = std::filesystem;
    std::vector<int> sizes = {100, 1000, 10000, 100000};
    fs::create_directories("bench_results");

    // Запустити бенчмарк операцій
    std::string ops_csv = "bench_results/ops_results.csv";
    run_all_benchmarks(sizes, 10, ops_csv);

    // Запустити бенчмарк сортування
    std::string sort_csv = "bench_results/sorting_results.csv";
    run_sorting_bench(sizes, 5, sort_csv);

    // Try to find project venv python
    std::string venv_python = ".venv/bin/python";
    std::string cmd;
    if (fs::exists(venv_python)) {
        cmd = venv_python + std::string(" plot_results.py --ops ") + ops_csv + " --sort " + sort_csv + " --out_dir bench_results --split";
    } else {
        cmd = std::string("python3 plot_results.py --ops ") + ops_csv + " --sort " + sort_csv + " --out_dir bench_results --split";
    }

    cout << "Запуск побудови графіків: " << cmd << endl;
    int rc = std::system(cmd.c_str());
    if (rc != 0) std::cerr << "Скрипт побудови графіків повернув код " << rc << endl;

    cout << "Готово. Результати у папці bench_results/" << endl;
    return 0;
}
