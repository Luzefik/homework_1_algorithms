#ifndef HOMEWORK_1_DATASTRUCTUREV3_H
#define HOMEWORK_1_DATASTRUCTUREV3_H

#include "IDataStructure.h"
#include <unordered_map>
#include <set>

class DataStructureV3 : public IDataStructure {
public:
    void init(std::vector<student> &basic_arr) override;
    void get_top_100() override;
    void set_grade_by_email(std::string student_email, float new_grade) override;
    std::string get_top_group() override;
    size_t get_memory_usage() override;

private:
    std::unordered_map<std::string, student*> students_emails; // email -> student*
    // впорядкований set для рейтингів; зберігаємо вказівник, компаратор використовує рейтинг та email
    struct Cmp3 {
        bool operator()(const student* a, const student* b) const {
            if (a->m_rating != b->m_rating) return a->m_rating > b->m_rating;
            return a->m_email < b->m_email;
        }
    };
    std::set<student*, Cmp3> sorted_rating;
    std::unordered_map<std::string, std::set<student*, Cmp3>::iterator> rating_index;
    std::unordered_map<std::string, std::pair<float,int>> students_groups;
    std::vector<student>* original_arr_ptr = nullptr;
};

#endif // HOMEWORK_1_DATASTRUCTUREV3_H
