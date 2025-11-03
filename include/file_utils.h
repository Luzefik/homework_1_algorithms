#ifndef HOMEWORK_1_FILE_UTILS_H
#define HOMEWORK_1_FILE_UTILS_H

#include <vector>
#include <string>
#include "student.h"

std::vector<student> readFile(const std::string &fileName);
void write_to_file_by_emails(std::vector<student*> &students, const std::string &file_name);

#endif // HOMEWORK_1_FILE_UTILS_H
