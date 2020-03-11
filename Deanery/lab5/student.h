#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Group;

class Student
{
private:
	int id;
	std::string fio;
	std::vector<int> marks;
	Group* group;

public:
	Student();
	Student(std::string);
	bool addToGroup(Group *);
	void addMark(int);
	void addMark(std::vector<int>);
	double getAverage();
	int getId();
	std::string getFIO();
	std::string getMarksForPrint();
	std::string getMarksForWrite();
	Group* getGroup();
	void setID(std::string);
};


#endif