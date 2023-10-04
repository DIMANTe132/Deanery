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
	void addMark(const int&);
	void addMark(std::vector<int>);
	float getAverage();
	int getId();
	std::string getFIO() const;
	std::string getMarksForPrint() const;
	std::string getMarksForWrite() const;
	Group* getGroup();
	void setID(std::string);
};


#endif