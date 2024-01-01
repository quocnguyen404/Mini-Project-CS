#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "helper.h"

using std::string;
using std::vector;

namespace Backend
{
    const int COURSE_ID_SIZE = 7;
    const string STUDENT_DATA_PATH = "students.txt";

    struct Student
    {
        int studentID; //8 chữ số theo định dạng 202xxxxx
        string fullName;
        float gpa;
        float cumulativeGPA;
        int semester;
    };

    struct Course
    {
        char courseID[COURSE_ID_SIZE]; //ITXXXX
        string courseName;
        Course* preCourse; //môn học tiền điều kiện
    };

    struct ClassStudent
    {
        Student* student;
        float midtermNote;
        float finalNote;
    };

    struct Class
    {
        int classID;//6 chữ số theo định dạng [2 chữ số cuối năm YY][4chữ số cuối của courseID]
        Course* course;
        vector<ClassStudent> studentList;
        int semester;
    };
}
