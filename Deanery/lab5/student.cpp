#include "student.h"
#include "group.h"
#include <string>
#include <numeric>
#include <sstream>


int staticID = 0;

Student::Student() : id(staticID), fio(""), group(std::weak_ptr<Group>()) // Поправка конструктора
{
	staticID++;
}


Student::Student(const std::string& FIO) : id(staticID), fio(FIO), group(std::weak_ptr<Group>()) // Поправка конструктора
{
	staticID++;
}


bool Student::addToGroup(const std::weak_ptr<Group>& group)
{
	if (group.lock()->search(getId()) != nullptr) // Замена стандартного поиска на наш
		return false;
	else
	{
		this->group = group; // Не имеет смысла добавлять студента здесь + при вызове Group::addStudent студет добавится дважды
		return true;
	};
};


void Student::addMark(const int& mark)
{
	marks.push_back(mark);
};


void Student::addMark(const std::vector<int>& mark)
{
	marks = mark;
};

float Student::getAverage() const
{
	if (marks.empty())
		return 0;
	else
		return std::accumulate(marks.begin(), marks.end(), float(0.0))/marks.size();
};


int Student::getId() const
{
	return id;
}


std::string Student::getFIO() const
{
	return fio;
}


std::string Student::getMarksForPrint() const
{
	std::string str = "";
	std::stringstream ss;
	for (const int& i : marks)
	{
		ss << i;
		ss << " ";
		str = ss.str();
	}
	return str;
}


std::string Student::getMarksForWrite() const
{
	std::string str = "";
	std::stringstream ss;
	for (const int& i : marks)
	{
		ss << i;
		str = ss.str();
	}
	return str;
}


std::weak_ptr<Group>& Student::getGroup()
{
	return group;
}


void Student::setID(const std::string& ID)
{
	std::stringstream ss;
	ss << ID;
	ss >> id;
}