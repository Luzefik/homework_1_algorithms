// DataStructureV1.h
#include "IDataStructure.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

class DataStructureV1 : public IDataStructure {
private:
    std::vector<student*> sorted_rating;
    std::unordered_map<std::string, student*> students_emails;
    std::unordered_map<std::string, std::pair<float, int>> students_groups;
    std::vector<student>* original_arr_ptr; // Для розрахунку пам'яті

public:
    void init(std::vector<student> &basic_arr) override;
    void get_top_100() override;
    void set_grade_by_email(std::string student_email, float new_grade) override;
    std::string get_top_group() override;
    size_t get_memory_usage() override;
};
