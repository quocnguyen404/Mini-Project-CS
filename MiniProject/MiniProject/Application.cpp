#include "Application.h"

namespace Application
{
	void createStudentList(vector<Student>& studentList, int amount)
	{
		ifstream studentFile;
		studentFile.open(STUDENT_DATA_PATH, ios::in);
		if (!studentFile)
		{
			cout << "Student file not exist\n";
			return;
		}

		string studentName;
		vector<string> names;
		while (!studentFile.eof())
		{
			getline(studentFile, studentName);
			names.push_back(studentName);
		}

		studentFile.close();
		Student student;

		for (int i = 0; i < amount; i++)
		{
			student.studentID = 20200000 + i;
			student.fullName = names[i];
			student.gpa = (float)(rand() % 100) / 20;
			student.cumulativeGPA = (float)(rand() % 100) / 20;
			student.semester = rand() % 8 + 1;
			studentList.push_back(student);
		}
	}

	void createThreeCourse(vector<Course>& courseList)
	{
		Course* ptCourse = new Course;
		strcpy_s(ptCourse->courseID, COURSE_ID_SIZE, "IT3140");
		ptCourse->courseName = "Programming Technique";
		ptCourse->preCourse = nullptr;
		courseList.push_back(*ptCourse);

		Course* seCourse = new Course;
		strcpy_s(seCourse->courseID, COURSE_ID_SIZE, "IT3180");
		seCourse->courseName = "Introduction to Software Engineering";
		seCourse->preCourse = nullptr;
		courseList.push_back(*seCourse);

		Course* saCourse = new Course;
		strcpy_s(saCourse->courseID, COURSE_ID_SIZE, "IT4501");
		saCourse->courseName = "Software Quality Assurance";
		saCourse->preCourse = nullptr;
		courseList.push_back(*saCourse);
	}

	Class* createClass(vector<Course>& courseList)
	{
		Class* nclass = new Class;
		cout << "Enter class ID: "; cin >> nclass->classID;
		string courseID;
		cout << "Enter course ID: "; cin.ignore(); getline(cin, courseID);
		Course* fCourse = findCourse(courseID, courseList);
		if (fCourse == nullptr)
			cout << "No course found\n";

		nclass->course = fCourse;
		cout << "Enter class semester: "; cin >> nclass->semester;
		return nclass;
	}

	Course* findCourse(string courseID, vector<Course>& courseList)
	{
		for (int i = 0; i < courseList.size(); i++)
		{
			if (strcmp(courseID.c_str(), courseList[i].courseID) != string::npos)
				return &courseList[i];
		}

		return nullptr;
	}

	void addStudentListToClass(vector<Class>& classList, vector<Student>& studentList)
	{
		int classID;
		cout << "Enter class ID: "; cin >> classID;
		Class* sclass = findClass(classID, classList);

		if (sclass == nullptr)
		{
			cout << "Not found class\n";
			return;
		}
		
		int amount;
		cout << "Enter student amount: "; cin >> amount;
		ClassStudent* nstudent;
		
		for (int i = 0; i < amount; i++)
		{
			int studentID;
			cout << "Enter student ID: "; cin >> studentID;
			Student* tStudent = findStudent(studentID, studentList);

			if (tStudent == nullptr)
			{
				cout << "Not found student\n";
				return;
			}

			nstudent = new ClassStudent;
			nstudent->student = tStudent;
			cout << "Enter " << nstudent->student->fullName << " midtermNote: "; cin >> nstudent->midtermNote;
			cout << "Enter " << nstudent->student->fullName << " finalNote: "; cin >> nstudent->finalNote;
			if (nstudent->midtermNote < 0 || nstudent->midtermNote > 10 || nstudent->finalNote < 0 || nstudent->finalNote> 10)
			{
				cout << "No found student\n";
				nstudent->midtermNote = 0;
				nstudent->finalNote = 0;
				return;
			}

			sclass->studentList.push_back(*nstudent);
		}
	}

	Class* findClass(int classID, vector<Class>& classList)
	{
		for (int i = 0; i < classList.size(); i++)
		{
			if (classID == classList[i].classID)
				return &classList[i];
		}
		return nullptr;
	}

	Student* findStudent(int studentID, vector<Student>& studentList)
	{
		for (int i = 0; i < studentList.size(); i++)
		{
			if (studentID == studentList[i].studentID)
				return &studentList[i];
		}
		return nullptr;
	}

	void sortAndPrint(Class& sclass)
	{
		for (int i = 0; i < sclass.studentList.size() - 1; i++)
		{
			for (int j = i + 1; j < sclass.studentList.size(); j++)
			{
				if (sclass.studentList[i].student->gpa < sclass.studentList[j].student->gpa)
					swap(sclass.studentList[i], sclass.studentList[j]);
			}
		}

		for (int i = 0; i < sclass.studentList.size(); i++)
		{
			printStudentInformation(&sclass.studentList[i]);
		}
	}

	void saveStudentInClass(vector<Class>& classList)
	{
		int classID;
		cout << "Enter class ID: "; cin >> classID;
		Class* sclass = findClass(classID, classList);
		if (sclass == nullptr)
		{
			cout << "Not found class\n";
			return;
		}

		string className = sclass->course->courseID + std::to_string(sclass->classID) + ".txt";
		fstream classFile;
		classFile.open(className.c_str(), ios::out);
		if (!classFile)
		{
			cout << "Not find file\n";
			return;
		}

		for (int i = 0; i < sclass->studentList.size(); i++)
		{
			classFile << sclass->studentList[i].student->fullName << " " << sclass->studentList[i].student->gpa << "\n";
		}

		classFile.close();
	}

	void printStudentInformation(ClassStudent* student)
	{
		cout << "StudentID : " << student->student->studentID << "\t"
			<< "StudentName : " << student->student->fullName << "\t"
			<< "MidtermNote : " << student->midtermNote << "\t"
			<< "FinalNote : " << student->finalNote << "\n";
	}
}