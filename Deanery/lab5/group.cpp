#include "group.h"
#include <time.h>  


Group::Group()
{
}


Group::Group(const std::string& name) : title(name), head(nullptr) // Поправка конструктора
{
}


bool Group::addStudent(std::shared_ptr<Student> student)
{
	if (search(student->getId()) != nullptr) { // Замена стандартного поиска на наш
		return false;   // this student has already been added to the group
	}
	else {
		student->addToGroup(this);
		students.push_back(student);
		return true;
	}
};


void Group::selectHead()
{
	size_t numberOfStudents = students.size();
	size_t index = rand() % numberOfStudents;
	head = students.at(index);
};


void Group::selectHead(std::shared_ptr<Student> student)
{
	head = student;
};


std::shared_ptr<Student> Group::search(const std::string& fio)
{
	for (auto& student : students) {
		if (student->getFIO() == fio) {
			return student;
		}
	}

	return nullptr;
};


std::shared_ptr<Student> Group::search(const int& id)
{
	for (auto& student : students) {
		if (student->getId() == id) {
			return student;
		}
	}

	return nullptr;
};


float Group::getGroupAverage() const
{
	size_t numberOfStudents = students.size();

	if (numberOfStudents == 0) {
		return 0;
	}

	float sum = 0;

	for (auto student : students) {
		sum += student->getAverage();
	}

	return sum / numberOfStudents;
};


void Group::expellStudent(const size_t& i)
{
	if (getStudent(i) == head)
		head = nullptr;
	students.erase(students.begin() + i);
};


std::string Group::getTitle() const
{
	return title;
}


std::shared_ptr<Student> Group::getHead()
{
	return head;
}

size_t Group::getStudentsCount() const
{
	return students.size();
}

std::shared_ptr<Student> Group::getStudent(const size_t& i)
{
	return students[i];
}
