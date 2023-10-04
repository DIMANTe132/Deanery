#ifndef DEANERY_H
#define DEANERY_H

#include "group.h"
#include "student.h"
#include <memory> // Использование умных указателей вместо сырых для избежания утечек

//class Group; // Лишнее forward declaration

class Deanery
{
private:
	std::vector<std::shared_ptr<Group>> groups; // Переход на умные указатели (переписывание всех методов где работали с сырыми указателями)

	//std::vector<std::string> split(const std::string& s, char delimiter); // Удаление этих методов из класса
	//std::vector<int> readMarks(std::string);
	//bool checkHead(Group*, Student* ,std::string); // Неиспользуемый метод, либо реализовать либо удалить
public:
	Deanery();  // read file, create groups
	void addRandomMarks();
	void statistics() const;// average mark for each student, average mark for each group
	void changeGroup();
	void expellStudents();  // if average mark < thresh
	void save() const; // Пометить все константные методы const (и так по всему проекту)
	void selectHead();
	void printData() const;
};


#endif