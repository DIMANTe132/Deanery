#ifndef DEANERY_H
#define DEANERY_H

#include <string>
#include <vector>
#include "group.h"
#include "student.h"
#include <time.h>

class Group;

class Deanery
{
private:
	std::vector<Group*> groups;

	std::vector<std::string> split(const std::string& s, char delimiter);
	std::vector<int> readMarks(std::string);
	bool checkHead(Group*, Student* ,std::string);
public:
	Deanery();  // read file, create groups
	void addRandomMarks();
	void statistics();  // average mark for each student, average mark for each group
	void changeGroup();
	void expellStudents();  // if average mark < thresh
	void save();
	void selectHead();
	void printData();
};


#endif