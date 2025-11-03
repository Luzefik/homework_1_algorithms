#ifndef HOMEWORK_1_DATASTRUCTUREV2_H
#define HOMEWORK_1_DATASTRUCTUREV2_H

#include "IDataStructure.h"
#include <map>
#include <set>
#include <unordered_map>

class DataStructureV2 : public IDataStructure {
public:
    void init(std::vector<student> &basic_arr) override;
    void get_top_100() override;
    void set_grade_by_email(std::string student_email, float new_grade) override;
    std::string get_top_group() override;
    size_t get_memory_usage() override;

private:
    // впорядкований map для email (std::map)
    std::map<std::string, student*> students_emails;
    // multiset for ratings (ordered descending by rating)
    struct Cmp {
        bool operator()(const student* a, const student* b) const {
            if (a->m_rating != b->m_rating) return a->m_rating > b->m_rating;
            return a->m_email < b->m_email;
        }
    };
    std::multiset<student*, Cmp> sorted_rating;
    // to quickly find iterator in multiset by email
    // швидкий доступ до ітератора в multiset по email
    std::unordered_map<std::string, std::multiset<student*, Cmp>::iterator> rating_index;
    std::map<std::string, std::pair<float,int>> students_groups;
    std::vector<student>* original_arr_ptr = nullptr;
};

#endif // HOMEWORK_1_DATASTRUCTUREV2_H
