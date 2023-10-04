#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <memory>

class Group;

class Student
{
private:
	int id;
	std::string fio;
	std::vector<int> marks;
	std::weak_ptr<Group> group; // Переход на умные указатели (переписывание всех методов где работали с сырыми указателями)

public:
	Student();
	Student(const std::string&);
	bool addToGroup(const std::weak_ptr<Group>&);
	void addMark(const int&);
	void addMark(const std::vector<int>&); // Передача без копирования
	float getAverage() const;
	std::weak_ptr<Group>& getGroup();
	void setID(const std::string&);
	int getId() const;
	std::string getFIO() const;
	std::string getMarksForPrint() const;
	std::string getMarksForWrite() const;
};


#endif