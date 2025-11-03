// IDataStructure.h
#ifndef HOMEWORK_1_IDATASTRUCTURE_H
#define HOMEWORK_1_IDATASTRUCTURE_H

#include <vector>
#include <string>
#include <cstddef>
#include "student.h"

class IDataStructure {
public:
    virtual ~IDataStructure() {}

    virtual void init(std::vector<student> &basic_arr) = 0;

    virtual void get_top_100() = 0;
    virtual void set_grade_by_email(std::string student_email, float new_grade) = 0;
    virtual std::string get_top_group() = 0;

    virtual std::size_t get_memory_usage() = 0;
};

#endif // HOMEWORK_1_IDATASTRUCTURE_H
