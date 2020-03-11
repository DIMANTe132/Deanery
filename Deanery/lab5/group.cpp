#include "group.h"
#include "student.h"
#include <time.h>  


class Student;

Group::Group()
{

}


Group::Group(std::string name)
{
	this->title = name;
	Student* head = nullptr;
}


bool Group::addStudent(Student * student)
{
	if (std::find(this->students.begin(), this->students.end(), student) != this->students.end()) {
		return false;   // this student has already been added to the group
	}
	else {
		student->addToGroup(this);
		this->students.push_back(student);
		return true;
	}
};


void Group::selectHead()
{
	int numberOfStudents = this->students.size();
	int index = rand() % numberOfStudents;
	this->head = this->students.at(index);
};


void Group::selectHead(Student* student)
{
	this->head = student;
};


Student * Group::search(std::string fio)
{
	for (Student* i : students) {
		if (i->getFIO() == fio) {
			return i;
		}
	}

	return nullptr;
};


Student * Group::search(int id)
{
	for (Student* i : students) {
		if (i->getId() == id) {
			return i;
		}
	}

	return nullptr;
};


double Group::getGroupAverage()
{
	int numberOfStudents = this->students.size();

	if (numberOfStudents == 0) {
		return 0;
	}

	float sum = 0;

	for (auto i : this->students) {
		sum += i->getAverage();
	}

	return sum / numberOfStudents;
};


void Group::expellStudent(Student* student ,int i)
{
	students.erase(students.begin() + i);
	delete student;
};


void Group::expellStudent(int i)
{
	this->students.erase(students.begin() + i);
};


std::string Group::getTitle()
{
	return this->title;
}


Student* Group::getHead()
{
	return this->head;
}