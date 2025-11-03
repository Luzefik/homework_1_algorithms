#include "benchmark_runner.h"
#include "file_utils.h"
#include "DataStructureV1.h"
#include "DataStructureV2.h"
#include "DataStructureV3.h"
#include "mem_utils.h"
#include "sorting.h"

#include <chrono>
#include <random>
#include <fstream>
#include <iostream>

using namespace std;
using namespace std::chrono;

struct BenchResult {
    string variant;
    int size;
    int op1; int op2; int op3; int total;
    double ops_per_sec;
    size_t mem_bytes;
    size_t rss_before;
    size_t rss_after;
    size_t rss_max;
};

template<typename DS>
BenchResult run_variant(const string &variant_name, vector<student> &data, int duration_sec,
                        const array<int,3> &ratio) {
    DS ds;
    auto init_start = high_resolution_clock::now();
    ds.init(data);
    auto init_end = high_resolution_clock::now();
    double init_ms = duration_cast<milliseconds>(init_end - init_start).count();

    random_device rd;
    mt19937 gen(rd());
    vector<int> weights;
    for (int i = 0; i < ratio[0]; ++i) weights.push_back(1);
    for (int i = 0; i < ratio[1]; ++i) weights.push_back(2);
    for (int i = 0; i < ratio[2]; ++i) weights.push_back(3);
    uniform_int_distribution<> op_dist(0, (int)weights.size()-1);
    uniform_int_distribution<> idx_dist(0, max(0, (int)data.size()-1));
    uniform_real_distribution<> rating_dist(0.0, 100.0);

    int op1=0,op2=0,op3=0;
    auto bench_start = high_resolution_clock::now();
    size_t rss_before = getCurrentRSS();
    size_t rss_max = rss_before;
    while (true) {
        auto now = high_resolution_clock::now();
        if (duration_cast<seconds>(now - bench_start).count() >= duration_sec) break;
        int op = weights[op_dist(gen)];
        if (op == 1) { ds.get_top_100(); op1++; }
        else if (op == 2) {
            int idx = idx_dist(gen);
            string email = data[idx].m_email;
            float newr = (float)rating_dist(gen);
            ds.set_grade_by_email(email, newr);
            op2++;
        } else { ds.get_top_group(); op3++; }
        size_t cur = getCurrentRSS(); if (cur > rss_max) rss_max = cur;
    }
    size_t rss_after = getCurrentRSS();
    auto bench_end = high_resolution_clock::now();

    int total = op1+op2+op3;
    double secs = duration_cast<duration<double>>(bench_end - bench_start).count();

    BenchResult r;
    r.variant = variant_name;
    r.size = (int)data.size();
    r.op1 = op1; r.op2 = op2; r.op3 = op3; r.total = total;
    r.ops_per_sec = total / secs;
    r.mem_bytes = ds.get_memory_usage();
    r.rss_before = rss_before; r.rss_after = rss_after; r.rss_max = rss_max;
    return r;
}

void run_all_benchmarks(const vector<int> &sizes, int duration_sec, const string &out_csv) {
    // Вибір співвідношень для варіантів (A:B:C)
    array<int,3> ratio_v1 = {2,10,5};
    array<int,3> ratio_v2 = {1,8,1};
    array<int,3> ratio_v3 = {3,5,2};

    ofstream ofs(out_csv);
    ofs << "variant,size,op1,op2,op3,total,ops_per_sec,mem_bytes,rss_before,rss_after,rss_max\n";

    for (int sz : sizes) {
        cout << "Виконується бенчмарк для розміру=" << sz << "\n";
        vector<student> data = readFile("students.csv");
        if (data.size() > (size_t)sz) data.resize(sz);

        // V1
        auto r1 = run_variant<DataStructureV1>("V1_vector", data, duration_sec, ratio_v1);
        ofs << r1.variant << "," << r1.size << "," << r1.op1 << "," << r1.op2 << "," << r1.op3 << "," << r1.total << "," << r1.ops_per_sec << "," << r1.mem_bytes << "," << r1.rss_before << "," << r1.rss_after << "," << r1.rss_max << "\n";

        // V2
        auto r2 = run_variant<DataStructureV2>("V2_map_multiset", data, duration_sec, ratio_v2);
        ofs << r2.variant << "," << r2.size << "," << r2.op1 << "," << r2.op2 << "," << r2.op3 << "," << r2.total << "," << r2.ops_per_sec << "," << r2.mem_bytes << "," << r2.rss_before << "," << r2.rss_after << "," << r2.rss_max << "\n";

        // V3
        auto r3 = run_variant<DataStructureV3>("V3_unordered_set", data, duration_sec, ratio_v3);
        ofs << r3.variant << "," << r3.size << "," << r3.op1 << "," << r3.op2 << "," << r3.op3 << "," << r3.total << "," << r3.ops_per_sec << "," << r3.mem_bytes << "," << r3.rss_before << "," << r3.rss_after << "," << r3.rss_max << "\n";
    }
    ofs.close();
    cout << "Бенчмарки завершені, результати у: " << out_csv << "\n";
}

// Sorting benchmarks: compare std::sort and quicksort (uses functions in sorting.cpp)
void run_sorting_bench(const vector<int> &sizes, int repeats, const string &out_csv) {
    ofstream ofs(out_csv);
    ofs << "algorithm,size,run,time_ms,mem_bytes\n";

    for (int sz : sizes) {
        cout << "Бенчмарк сортування для розміру=" << sz << "\n";
        vector<student> data = readFile("students.csv");
        if (data.size() > (size_t)sz) data.resize(sz);

        // Prepare pointer arrays for sorting
        for (int run = 1; run <= repeats; ++run) {
            vector<student*> a_std, a_quick;
            a_std.reserve(data.size()); a_quick.reserve(data.size());
            for (size_t i = 0; i < data.size(); ++i) { a_std.push_back(&data[i]); a_quick.push_back(&data[i]); }

            auto t1s = high_resolution_clock::now();
            sort_default_email(a_std);
            auto t1e = high_resolution_clock::now();
            auto d1 = duration_cast<milliseconds>(t1e - t1s).count();
            ofs << "std::sort," << data.size() << "," << run << "," << d1 << "," << 0 << "\n";

            auto t2s = high_resolution_clock::now();
            sort_quick_sort_email(a_quick);
            auto t2e = high_resolution_clock::now();
            auto d2 = duration_cast<milliseconds>(t2e - t2s).count();
            ofs << "quick_sort," << data.size() << "," << run << "," << d2 << "," << 0 << "\n";

            bool ok = true;
            for (size_t i = 0; i < a_std.size(); ++i) {
                if (a_std[i]->m_email != a_quick[i]->m_email) { ok = false; break; }
            }
            cout << "  прогін=" << run << " std::sort=" << d1 << "ms quick=" << d2 << "ms коректність=" << (ok?"ТАК":"НІ") << "\n";
        }
    }
    ofs.close();
    cout << "Бенчмарки сортування завершені, результати у: " << out_csv << "\n";
}
