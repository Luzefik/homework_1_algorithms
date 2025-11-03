#include "file_utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<student> readFile(const string &fileName) {
    vector<student> students;
    fstream file(fileName, ios::in);
    if (file.is_open()) {
        string line;
        getline(file, line);

        while (getline(file, line)) {
            student temp_student;
            stringstream ss(line);
            string field;
            getline(ss, field, ',');
            temp_student.name = field;
            getline(ss, field, ',');
            temp_student.m_surname = field;
            getline(ss, field, ',');
            temp_student.m_email = field;
            getline(ss, field, ',');
            temp_student.m_birth_year = stoi(field);
            getline(ss, field, ',');
            temp_student.m_birth_month = stoi(field);
            getline(ss, field, ',');
            temp_student.m_birth_day = stoi(field);
            getline(ss, field, ',');
            temp_student.m_group = field;
            getline(ss, field, ',');
            temp_student.m_rating = stof(field);
            getline(ss, field, ',');
            temp_student.m_phone_number = field;
            students.push_back(temp_student);
        }
    }
    file.close();
    return students;
}


void write_to_file_by_emails(vector<student*> &students, const string &file_name) {
    fstream file(file_name, ios::out);
    if (file.is_open()) {
        file << "m_name,m_surname,m_email,m_birth_year,m_birth_month,m_birth_day,m_group,m_rating,m_phone_number" << endl;
        for (size_t i = 0; i < students.size(); i++) {
            file << students[i]->name << ","
                 << students[i]->m_surname << ","
                 << students[i]->m_email << ","
                 << students[i]->m_birth_year << ","
                 << students[i]->m_birth_month << ","
                 << students[i]->m_birth_day << ","
                 << students[i]->m_group << ","
                 << students[i]->m_rating << ","
                 << students[i]->m_phone_number << endl;

        }
    }
    file.close();
}
