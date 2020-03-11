#include <string>
#include "student.h"
#include "group.h"
#include <numeric>
#include <sstream>


class group;

int staticID = 0;

Student::Student()
{

}


Student::Student(std::string FIO)
{
	this->fio = FIO;
	this->id = staticID;
	staticID++;
}


bool Student::addToGroup(Group* group)
{
	if (std::find(group->students.begin(), group->students.end(), this) != group->students.end())
	{
		return false;
	}
	else
	{
		this->group = group;
		group->students.push_back(this);
		return true;
	};
};


void Student::addMark(int mark)
{
	this->marks.push_back(mark);
};


void Student::addMark(std::vector<int> mark)
{
	this->marks = mark;
};

double Student::getAverage()
{
	if (this->marks.empty())
		return 0;
	else
		return std::accumulate(this->marks.begin(), this->marks.end(), 0.0)/this->marks.size();
};


int Student::getId()
{
	return this->id;
}


std::string Student::getFIO()
{
	return this->fio;
}


std::string Student::getMarksForPrint()
{
	std::string str = "";
	std::stringstream ss;
	for (int i : marks)
	{
		ss << i;
		ss << " ";
		str = ss.str();
	}
	return str;
}


std::string Student::getMarksForWrite()
{
	std::string str = "";
	std::stringstream ss;
	for (int i : marks)
	{
		ss << i;
		str = ss.str();
	}
	return str;
}


Group* Student::getGroup()
{
	return this->group;
}


void Student::setID(std::string ID)
{
	std::stringstream ss;
	ss << ID;
	ss >> this->id;
}