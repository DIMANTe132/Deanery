#include "deanery.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <time.h>

//class Group; // Лишнее forward declaration


std::vector<std::string> split(const std::string& s, const char& delimiter)
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


std::vector<int> readMarks(const std::string& Marks)
{
	std::vector<int> marks;
	std::stringstream str;
	int mark;

	for (size_t i = 0; i < Marks.length(); i++)
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


Deanery::Deanery()  // read file, create groups
{
	std::string path("students.txt"); // Вынос пути в отдельную переменную

	std::ifstream file(path);

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

		std::shared_ptr<Student> student(new Student(info[0]));   // info[0] - FIO

		student->setID(info[4]);

		if (info[3] != "")   // info[3] - marks
			student->addMark(readMarks(info[3]));

		if (groups.empty())
		{
			std::shared_ptr<Group> group(new Group(info[1]));
			groups.push_back(group);
			group->addStudent(student, group); // Добавляем студента в группу, а не наоборот (и так во всем файле)

			if (info[2] == "Head")
				group->selectHead(student);
		}

		else
		{
			bool addedToGroup = false;

			for (auto& group : groups) // Замена в foreach тип на auto (во всем проекте)
			{
				if (group->getTitle() == info[1])
				{
					group->addStudent(student, group);
					addedToGroup = true;

					if (info[2] == "Head")
						group->selectHead(student);
				}
			}

			if (addedToGroup == false)
			{
				std::shared_ptr<Group> group(new Group(info[1]));
				groups.push_back(group);
				group->addStudent(student, group);

				if (info[2] == "Head")
					group->selectHead(student);
			}
		}
	}
};


void Deanery::addRandomMarks()
{
	for (auto& group : groups)
	{
		for (int i = 0; i < group->getStudentsCount(); i++)
		{
			int newMark = rand() % 10 + 1;
			group->getStudent(i)->addMark(newMark);
		}
	}

	std::cout << "Marks were added" << std::endl;
}


void Deanery::statistics() const // average mark for each student, average mark for each group
{
	std::cout << "Student statistics:" << std::endl;

	for (auto& group : groups) 
	{
		std::cout << group->getTitle() << ":" << std::endl;

		for (int i = 0; i < group->getStudentsCount(); i++)
		{
			std::cout << i + 1 << ": " << group->getStudent(i)->getFIO() << ": " << group->getStudent(i)->getAverage() << std::endl;
		}

		std::cout << std::endl;
	}

	std::cout << "Group statistics:" << std::endl;

	for (auto& group : groups) 
	{
		std::cout << group->getTitle() << ": " << group->getGroupAverage() << std::endl;
	}
}


void Deanery::changeGroup()
{
	int id;
	size_t i;
	bool searchStudent = false;
	std::shared_ptr<Student> student;

	std::cout << "Enter the ID of student: ";
	std::cin >> id;

	for (auto& group : groups)
	{
		for (i = 0; i < group->getStudentsCount(); i++)
		{
			if (group->getStudent(i)->getId() == id)
			{
				student = group->getStudent(i);
				searchStudent = true;
				break;
			}
		}
		if (searchStudent)
			break;
	}

	if (!searchStudent)
	{
		std::wcout << "Student was not found" << std::endl;
		return;
	}

	std::string title;
	std::cout << "Enter the group to transfer the student to: ";
	std::cin >> title;
	for (auto& group : groups)
	{
		if (title == group->getTitle())
		{
			if (student->getGroup().lock().get() == group.get())
			{
				std::cout << "Student is already in this group" << std::endl;
			}
			else
			{
				student->getGroup().lock()->expellStudent(i);
				group->addStudent(student, group);

				std::cout << "Group was changed" << std::endl;
			}
			return;
		}
	}
	std::cout << "Group was not found" << std::endl;
	return;
}


void Deanery::expellStudents()  // if average mark < thresh
{
	for (auto& group : groups)
	{
		if (group->getStudentsCount() > 0)
		{
			for (size_t i = group->getStudentsCount() - 1; i > 0; i--)
			{
				if (group->getStudent(i)->getAverage() < 4 && group->getStudent(i)->getAverage() != 0)
				{
					group->expellStudent(i);
				}
			}
		}
	}

	std::cout << "The students were expelled" << std::endl;
}


void Deanery::save() const
{
	std::string path("students.txt"); // Вынос пути в отдельную переменную
	std::ofstream file(path);

	if (!file)
	{
		std::cout << "File was not found!" << std::endl;
		return;
	}

	for (auto& group : groups)
	{
		std::shared_ptr<Student> head = group->getHead();

		for (int i = 0; i < group->getStudentsCount(); i++)
		{
			file << group->getStudent(i)->getFIO() << ":" << group->getTitle() << ":";

			if (group->getStudent(i) == head)
				file << "Head" << ":" << group->getStudent(i)->getMarksForWrite() << ":" << group->getStudent(i)->getId() << " " << std::endl;

			else
				file << ":" << group->getStudent(i)->getMarksForWrite() << ":" << group->getStudent(i)->getId() << " " << std::endl;
		}
	}

	file.close();
	std::cout << "Data was saved" << std::endl;
};


void Deanery::selectHead()
{
	for (auto& group : groups)
	{
		group->selectHead();
	}

	std::cout << "Heads were selected" << std::endl;
};


void Deanery::printData() const
{
	std::cout << "Student data:" << std::endl;

	for (auto& group : groups)
	{
		std::cout << group->getTitle() << ":" << std::endl;

		for (int i = 0; i < group->getStudentsCount(); i++)
		{
			if (group->getStudent(i) == group->getHead())
				std::cout << "ID: " << group->getStudent(i)->getId() << ": " << group->getStudent(i)->getFIO() << ": " << group->getStudent(i)->getMarksForPrint() << " - Head" << std::endl;
			
			else
				std::cout << "ID: " << group->getStudent(i)->getId() << ": " << group->getStudent(i)->getFIO() << ": " << group->getStudent(i)->getMarksForPrint() << std::endl;
		}

		std::cout << std::endl;
	}
};