#include "DataStructureV3.h"

using namespace std;

void DataStructureV3::init(std::vector<student> &basic_arr) {
    original_arr_ptr = &basic_arr;
    for (size_t i = 0; i < basic_arr.size(); ++i) {
        student* s = &basic_arr[i];
        students_emails[s->m_email] = s;
        auto it = sorted_rating.insert(s).first;
        rating_index[s->m_email] = it;
        students_groups[s->m_group].first += s->m_rating;
        students_groups[s->m_group].second++;
    }
}

void DataStructureV3::get_top_100() {
    int cnt = 0;
    for (auto it = sorted_rating.begin(); it != sorted_rating.end() && cnt < 100; ++it, ++cnt) {
        volatile float r = (*it)->m_rating; (void)r;
    }
}

void DataStructureV3::set_grade_by_email(std::string student_email, float new_grade) {
    auto it = students_emails.find(student_email);
    if (it == students_emails.end()) return;
    student* s = it->second;
    float old = s->m_rating;
    std::string g = s->m_group;
    students_groups[g].first += (new_grade - old);
    auto rit = rating_index.find(student_email);
    if (rit != rating_index.end()) {
        sorted_rating.erase(rit->second);
    }
    s->m_rating = new_grade;
    auto nit = sorted_rating.insert(s).first;
    rating_index[student_email] = nit;
}

std::string DataStructureV3::get_top_group() {
    std::string best = "";
    double max_avg = -1.0;
    for (auto const& kv : students_groups) {
        if (kv.second.second == 0) continue;
        double avg = kv.second.first / kv.second.second;
        if (avg > max_avg) {
            max_avg = avg;
            best = kv.first;
        }
    }
    return best;
}

size_t DataStructureV3::get_memory_usage() {
    if (!original_arr_ptr) return 0;
    size_t mem = 0;
    mem += original_arr_ptr->capacity() * sizeof(student);
    for (const auto &s : *original_arr_ptr) {
        mem += s.name.capacity();
        mem += s.m_surname.capacity();
        mem += s.m_email.capacity();
        mem += s.m_group.capacity();
        mem += s.m_phone_number.capacity();
    }
    mem += sorted_rating.size() * sizeof(student*);
    mem += students_emails.size() * (sizeof(std::string) + sizeof(student*));
    mem += rating_index.size() * (sizeof(std::string) + sizeof(void*));
    mem += students_groups.size() * (sizeof(std::string) + sizeof(std::pair<float,int>));
    return mem;
}
