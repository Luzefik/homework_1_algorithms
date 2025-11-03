#include "DataStructureV1.h"
#include "sorting.h"
#include <iostream>
#include <algorithm>

using namespace std;

void DataStructureV1::init(vector<student> &basic_arr) {
    original_arr_ptr = &basic_arr;

    for (size_t i = 0; i < basic_arr.size(); i++) {
        student* student_ptr = &basic_arr[i];

        sorted_rating.push_back(student_ptr);
        students_emails[student_ptr->m_email] = student_ptr;

        students_groups[student_ptr->m_group].first += student_ptr->m_rating;
        students_groups[student_ptr->m_group].second++;
    }

    if (!sorted_rating.empty()) {
        quicksort_grade(sorted_rating, 0, sorted_rating.size() - 1);
    }
}

void DataStructureV1::get_top_100() {
    int limit = min((size_t)100, sorted_rating.size());
    (void)limit;
}

void DataStructureV1::set_grade_by_email(string student_email, float new_grade) {
    auto it = students_emails.find(student_email);
    if (it == students_emails.end()) return; // Студента не знайдено

    student* s_ptr = it->second;
    float old_rating = s_ptr->m_rating;
    string group_name = s_ptr->m_group;


    s_ptr->m_rating = new_grade;

    students_groups[group_name].first += (new_grade - old_rating);

    int index = -1;
    for (int i = 0; i < sorted_rating.size(); i++) {
        if (sorted_rating[i]->m_email == student_email) {
            index = i;
            break;
        }
    }

    if (index == -1) return;

    while (index > 0 && sorted_rating[index]->m_rating > sorted_rating[index - 1]->m_rating) {
        swap(sorted_rating[index], sorted_rating[index - 1]);
        index--;
    }

    while (index < sorted_rating.size() - 1 && sorted_rating[index]->m_rating < sorted_rating[index + 1]->m_rating) {
        swap(sorted_rating[index], sorted_rating[index + 1]);
        index++;
    }
}

string DataStructureV1::get_top_group() {
    string best_group = "";
    float max_avg = -1.0;

    for (auto const& [group_name, data] : students_groups) {
        if (data.second == 0) continue;

        float average = data.first / data.second;
        if (max_avg < average) {
            max_avg = average;
            best_group = group_name;
        }
    }
    return best_group;
}

size_t DataStructureV1::get_memory_usage() {
    if (original_arr_ptr == nullptr) return 0;

    size_t memory = 0;

    memory += original_arr_ptr->capacity() * sizeof(student);
    for (const auto& s : *original_arr_ptr) {
        memory += s.name.capacity();
        memory += s.m_surname.capacity();
        memory += s.m_email.capacity();
        memory += s.m_group.capacity();
        memory += s.m_phone_number.capacity();
    }

    memory += sorted_rating.capacity() * sizeof(student*);

    memory += students_emails.size() * (sizeof(string) + sizeof(student*)) * 2;

    memory += students_groups.size() * (sizeof(string) + sizeof(pair<float, int>)) * 2;

    return memory;
}
