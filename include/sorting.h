// sorting.h
#ifndef HOMEWORK_1_SORTING_H
#define HOMEWORK_1_SORTING_H

#include <vector>
#include "student.h"

int partition(std::vector<student*> &arr, int low, int high);
void quicksort_grade(std::vector<student*> &arr, int low, int high);
void quicksort_email(std::vector<student*> &arr, int low, int high);

void sort_default_email(std::vector<student*> &students);
void sort_quick_sort_email(std::vector<student*> &students);
void benchmark_sorting(std::vector<student> &basic_arr);

#endif // HOMEWORK_1_SORTING_H
