#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

#include "student.h"
#include "file_utils.h"
#include "sorting.h"
#include "DataStructureV1.h"

using namespace std;
using namespace std::chrono;

int main() {
    cout << "Варіант V5, Співвідношення 2:10:5, Сортування S1" << endl;

    vector<int> sizes = {100, 1000, 10000, 100000};

    for (int size : sizes) {
        vector<student> basic_arr = readFile("students.csv");
        if (basic_arr.size() > size) basic_arr.resize(size);

        if (basic_arr.empty()) {
            cout << "\n=== Бенчмарк для 0 студентів (пропускаємо) ===" << endl;
            continue;
        }

        cout << "\n=== Бенчмарк для " << basic_arr.size() << " студентів ===" << endl;

        DataStructureV1 ds;
        ds.init(basic_arr);
       cout << "Використана пам'ять (приблизно): " << fixed << setprecision(2)
           << ds.get_memory_usage() / (1024.0 * 1024.0) << " MB" << endl;

        int duration_sec = 10;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> op_dist(1, 17);
        uniform_int_distribution<> email_dist(0, basic_arr.size() - 1);
        uniform_real_distribution<> rating_dist(0.0, 100.0);

        int op1_count = 0, op2_count = 0, op3_count = 0;
        auto bench_start = high_resolution_clock::now();
        while (true) {
            auto current = high_resolution_clock::now();
            auto elapsed = duration_cast<seconds>(current - bench_start);
            if (elapsed.count() >= duration_sec) break;

            int op_type = op_dist(gen);
            if (op_type <= 2) {
                ds.get_top_100();
                op1_count++;
            } else if (op_type <= 12) {
                int idx = email_dist(gen);
                string email = basic_arr[idx].m_email;
                float new_rating = rating_dist(gen);
                ds.set_grade_by_email(email, new_rating);
                op2_count++;
            } else {
                ds.get_top_group();
                op3_count++;
            }
        }

        int total_ops = op1_count + op2_count + op3_count;
        cout << "Виконано операцій за " << duration_sec << " секунд: " << total_ops << endl;
        cout << "  - операція 1 (get_top_100): " << op1_count << endl;
        cout << "  - операція 2 (set_grade_by_email): " << op2_count << endl;
        cout << "  - операція 3 (get_top_group): " << op3_count << endl;
        cout << "Операцій за секунду: " << (total_ops / (double)duration_sec) << endl;

        benchmark_sorting(basic_arr);
    }

    cout << "\n=== Фінальне сортування всіх студентів ===" << endl;
    vector<student> all_students = readFile("students.csv");
    vector<student*> students_ptrs;
    for (size_t i = 0; i < all_students.size(); i++) students_ptrs.push_back(&all_students[i]);

    auto sort_start = high_resolution_clock::now();
    sort_quick_sort_email(students_ptrs);
    auto sort_end = high_resolution_clock::now();
    auto sort_duration = duration_cast<milliseconds>(sort_end - sort_start);
    cout << "Час сортування: " << sort_duration.count() << " мс" << endl;

    write_to_file_by_emails(students_ptrs, "sorted_students.csv");
    cout << "Результат збережено у sorted_students.csv" << endl;

    return 0;
}
