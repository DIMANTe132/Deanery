#include "deanery.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Group;

Deanery::Deanery()  // read file, create groups
{
	std::ifstream file("students.txt");

	if (!file)
	{
		std::cout << "File was not found!" << std::endl;
		return;
	}

	std::string s;

	while (!file.eof())
	{
		std::getline(file, s);

		if (s == "")
		{
			file.close();
			std::cout << "File is ok" << std::endl;
			std::cout << std::endl;
			return;
		}

		std::vector<std::string> info = split(s, ':');

		Student* student = new Student(info[0]);   // info[0] - FIO

		student->setID(info[4]);

		if (info[3] != "")   // info[3] - marks
			student->addMark(readMarks(info[3]));

		if (groups.empty())
		{
			Group* group = new Group(info[1]);
			groups.push_back(group);
			student->addToGroup(group);

			if (info[2] == "Head")
				group->selectHead(student);
		}

		else
		{
			bool addedToGroup = false;

			for (Group* group : groups)
			{
				if (group->getTitle() == info[1])
				{
					student->addToGroup(group);
					addedToGroup = true;

					if (info[2] == "Head")
						group->selectHead(student);
				}
			}

			if (addedToGroup == false)
			{
				Group* group = new Group(info[1]);
				groups.push_back(group);
				student->addToGroup(group);

				if (info[2] == "Head")
					group->selectHead(student);
			}
		}
	}
};


void Deanery::addRandomMarks()
{
	for (Group* group : groups)
	{
		for (int i = 0; i < group->students.size(); i++)
		{
			int newMark = rand() % 10 + 1;
			group->students[i]->addMark(newMark);
		}
	}

	std::cout << "Marks were added" << std::endl;
}


void Deanery::statistics()  // average mark for each student, average mark for each group
{
	std::cout << "Student statistics:" << std::endl;

	for (Group* group : groups) 
	{
		std::cout << group->getTitle() << ":" << std::endl;

		for (int i = 0; i < group->students.size(); i++)
		{
			std::cout << i + 1 << ": " << group->students[i]->getFIO() << ": " << group->students[i]->getAverage() << std::endl;
		}

		std::cout << std::endl;
	}

	std::cout << "Group statistics:" << std::endl;

	for (Group* group : groups) 
	{
		std::cout << group->getTitle() << ": " << group->getGroupAverage() << std::endl;
	}
}


void Deanery::changeGroup()
{
	int ID;
	int k;
	std::string title;
	bool searchStudent = false;
	Student* student = new Student();

	std::cout << "Enter the ID of student: ";
	std::cin >> ID;
	std::cout << "Enter the group to transfer the student to: ";
	std::cin >> title;

	for (Group* group : groups)
	{
		for (int i = 0; i < group->students.size(); i++)
		{
			if (group->students[i]->getId() == ID)
			{
				student = group->students[i];
				searchStudent = true;
				k = i;
			}
		}	
	}

	if (searchStudent == false)
	{
		std::wcout << "Student was not found" << std::endl;
		return;
	}

	for (Group* group : groups)
	{
		if (title == group->getTitle())
		{
			if (student->getGroup() == group)
			{
				std::cout << "Student is already in this group" << std::endl;
			}

			else
			{
				student->getGroup()->expellStudent(k);
				student->addToGroup(group);

				std::cout << "Group was changed" << std::endl;
				return;
			}
		}
	}
	std::cout << "Group was not found" << std::endl;
	return;
}


void Deanery::expellStudents()  // if average mark < thresh
{
	for (Group* group : groups)
	{
		for (int i = 0; i < group->students.size(); i++)
		{
			if (group->students[i]->getAverage() < 4 && group->students[i]->getAverage() != 0)
			{
				group->expellStudent(group->students[i], i);
				i--;
			}
		}
	}

	std::cout << "The students were expelled" << std::endl;
}


void Deanery::save()
{
	std::ofstream file("students.txt");

	if (!file)
	{
		std::cout << "File was not found!" << std::endl;
		return;
	}

	for (Group* group : groups)
	{
		Student* head = group->getHead();

		for (int i = 0; i < group->students.size(); i++)
		{
			file << group->students[i]->getFIO() << ":" << group->getTitle() << ":";

			if (group->students[i] == head)
				file << "Head" << ":" << group->students[i]->getMarksForWrite() << ":" << group->students[i]->getId() << " " << std::endl;

			else
				file << ":" << group->students[i]->getMarksForWrite() << ":" << group->students[i]->getId() << " " << std::endl;
		}
	}

	file.close();
	std::cout << "Data was saved" << std::endl;
};


void Deanery::selectHead()
{
	for (Group* group : groups)
	{
		group->selectHead();
	}

	std::cout << "Heads were selected" << std::endl;
};


void Deanery::printData()
{
	std::cout << "Student data:" << std::endl;

	for (Group* group : groups)
	{
		std::cout << group->getTitle() << ":" << std::endl;
		Student* head = group->getHead();

		for (int i = 0; i < group->students.size(); i++)
		{
			if (group->students[i] == head)
				std::cout << "ID: " << group->students[i]->getId() << ": " << group->students[i]->getFIO() << ": " << group->students[i]->getMarksForPrint() << " - Head" << std::endl;
			
			else
				std::cout << "ID: " << group->students[i]->getId() << ": " << group->students[i]->getFIO() << ": " << group->students[i]->getMarksForPrint() << std::endl;
		}

		std::cout << std::endl;
	}
};


std::vector<std::string> Deanery::split(const std::string& s, char delimiter)
{
	std::vector<std::string> result;
	std::string token;
	std::istringstream tokenStream(s);

	while (std::getline(tokenStream, token, delimiter))
	{
		result.push_back(token);
	}

	return result;
}


std::vector<int> Deanery::readMarks(std::string Marks)
{
	std::vector<int> marks;
	std::stringstream str;
	int mark;

	for (int i = 0; i < Marks.length(); i++)
	{
		if (Marks[i] == '1')
		{
			if (Marks[i + 1])
			{
				if (Marks[i + 1] == '0')
				{
					str << Marks[i] << Marks[i + 1];
					str >> mark;
					marks.push_back(mark);
					i++;
				}

				else
				{
					str << Marks[i];
					str >> mark;
					marks.push_back(mark);
				}
			}

			else
			{
				str << Marks[i];
				str >> mark;
				marks.push_back(mark);
			}
		}
		else
		{
			str << Marks[i];
			str >> mark;
			marks.push_back(mark);
		}
		str = std::stringstream();
	}
	return marks;
}