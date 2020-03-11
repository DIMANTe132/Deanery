#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>

class Student;

class Group
{
private:
	std::string title;
	Student * head;

public:
	std::vector<Student*> students;
	Group();
	Group(std::string);
	bool addStudent(Student *);
	void selectHead();
	void selectHead(Student*);
	Student * search(std::string);
	Student * search(int);
	double getGroupAverage();
	void expellStudent(Student* ,int);
	void expellStudent(int);
	std::string getTitle();
	Student* getHead();
};


#endif