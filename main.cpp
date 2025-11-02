#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct student {
    string name;
    string m_surname;
    string m_email;
    int m_birth_year;
    int m_birth_month;
    int m_birth_day;
    string m_group;
    float m_rating;
    string m_phone_number;
};


vector<student> readFile(string fileName) {
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
int partiotion(vector<student*> &arr, int low, int high) {
    float pivot = arr[high]->m_rating;
    int pi = low - 1;

    for (int j = low; j < high; j ++) {
        if (arr[j]->m_rating > pivot) {
            pi++;
            swap(arr[j], arr[pi]);
        }

    }
    swap(arr[pi+1], arr[high]);
    return pi+1;
}

void quicksort_grade(vector<student*> &arr, int low, int high) {
    if (low < high) {
        int pi = partiotion(arr, low, high);
        quicksort_grade(arr, low, pi - 1);
        quicksort_grade(arr, pi + 1, high);
    }
}

void sort_by_grade(vector<student*> &students) {
    quicksort_grade(students, 0, students.size() - 1);

}

void set_grade_by_email(unordered_map<string, student*> &students_emails,
                        vector<student*> &rating,
                        string student_email,
                        float new_grade) {
    students_emails[student_email]->m_rating  = new_grade;
    int index = -1;
    for (int i = 1; i < rating.size(); i ++) {
        if (rating[i]->m_email == student_email) {
            index = i;
        }
        while (index > 0 && rating[index]->m_rating > rating[index - 1]->m_rating) {
            swap(rating[index], rating[index - 1]);
            index--;
        }

        while (index < rating.size() - 1 && rating[index]->m_rating < rating[index + 1]->m_rating) {
            swap(rating[index], rating[index + 1]);
            index++;
        }
    }
}
void get_by_email (vector<student> students) {
    return;
}

void get_top_100(vector<student*> &students) {
    for (int i = 0; i < 100; i ++) {
        cout << i+1 << ": Середній бал: "
                    << students[i]->m_rating
                    << " " << students[i]->name
                    << " " << students[i]->m_surname
                    << " " << students[i]->m_email
                    << endl;
    }
}

int main() {
    vector<student> basic_arr = readFile("students.csv");
    vector<student*> sorted_rating;
    unordered_map<string, student*> students_emails;

    for (int i = 0; i < basic_arr.size(); i++) {
        student* student_ptr = &basic_arr[i];
        sorted_rating.push_back(student_ptr);
        students_emails[student_ptr->m_email] = student_ptr;
    }


    sort_by_grade(sorted_rating);

    get_top_100(sorted_rating);

    set_grade_by_email(
        students_emails,
        sorted_rating,
        "ivan.kravchenko@student.org",
        100.3);

    get_top_100(sorted_rating);

    return 0;
}