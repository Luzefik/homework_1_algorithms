#include "sorting.h"
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;


int partition(vector<student*> &arr, int low, int high) {
    float pivot = arr[high]->m_rating;
    int pi = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j]->m_rating > pivot) {
            pi++;
            swap(arr[j], arr[pi]);
        }
    }
    swap(arr[pi + 1], arr[high]);
    return pi + 1;
}

void quicksort_grade(vector<student*> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort_grade(arr, low, pi - 1);
        quicksort_grade(arr, pi + 1, high);
    }
}

int partition_email(vector<student*> &arr, int low, int high) {
    string pivot = arr[high]->m_email;
    int pi = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j]->m_email < pivot) {
            pi++;
            swap(arr[j], arr[pi]);
        }
    }
    swap(arr[pi + 1], arr[high]);
    return pi + 1;
}

void quicksort_email(vector<student*> &arr, int low, int high) {
    if (low < high) {
        int pi = partition_email(arr, low, high);
        quicksort_email(arr, low, pi - 1);
        quicksort_email(arr, pi + 1, high);
    }
}
void sort_default_email(vector<student*> &students) {
    sort(students.begin(), students.end(), [](student* a, student* b) {
        return a->m_email < b->m_email;
    });
}

void sort_quick_sort_email(vector<student*> &students) {
    if (students.empty()) return;
    quicksort_email(students, 0, students.size() - 1);
}

// === БЕНЧМАРК СОРТУВАННЯ ===

void benchmark_sorting(vector<student> &students) {
    cout << "\n=== Бенчмарк сортування для " << students.size() << " студентів ===" << endl;

    vector<student*> students_std, students_quick;
    for (size_t i = 0; i < students.size(); i++) {
        students_std.push_back(&students[i]);
        students_quick.push_back(&students[i]);
    }

    auto start1 = high_resolution_clock::now();
    sort_default_email(students_std);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(end1 - start1);

    auto start2 = high_resolution_clock::now();
    sort_quick_sort_email(students_quick);
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(end2 - start2);

    cout << "std::sort: " << duration1.count() << " мс" << endl;
    cout << "QuickSort: " << duration2.count() << " мс" << endl;
    bool correct = true;
    for (size_t i = 0; i < students_std.size(); i++) {
        if (students_std[i]->m_email != students_quick[i]->m_email) {
            correct = false;
            break;
        }
    }
    cout << "Результати співпадають: " << (correct ? "ТАК" : "НІ") << endl;
}
