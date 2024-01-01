#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

const int COURSE_ID_SIZE = 7;
const string STUDENT_DATA_PATH = "students.txt";

namespace Application
{

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

	void createStudentList(vector<Student>& studentList, int amount);
	void createStudentList(vector<Student>& studentList, int amount);
	void createThreeCourse(vector<Course>& courseList);
	Class* createClass(vector<Course>& courseList);
	Course* findCourse(string courseID, vector<Course>& courseList);
	void addStudentListToClass(vector<Class>& classList, vector<Student>& studentList);
	Class* findClass(int classID, vector<Class>& classList);
	Student* findStudent(int studentID, vector<Student>& studentList);
	void sortAndPrint(Class& sclass);
	void saveStudentInClass(vector<Class>& classList);
	void printStudentInformation(ClassStudent* student);
}