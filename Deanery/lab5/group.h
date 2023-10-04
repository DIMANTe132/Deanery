#ifndef GROUP_H
#define GROUP_H

#include "student.h"
#include <string>
#include <vector>
#include <memory>


class Group
{
private:
	std::string title;
	std::shared_ptr<Student> head; // Переход на умные указатели (переписывание всех методов где работали с сырыми указателями)
	std::vector<std::shared_ptr<Student>> students; // Перенос всех полей класса в private блок

public:
	Group();
	Group(const std::string&);
	bool addStudent(std::shared_ptr<Student>&, const std::shared_ptr<Group>&);
	void selectHead();
	void selectHead(std::shared_ptr<Student>&);
	std::shared_ptr<Student> search(const std::string&);
	std::shared_ptr<Student> search(const int&);
	float getGroupAverage() const;
	//void expellStudent(std::shared_ptr<Student>&, size_t&); // Две реализации этого метода можно объеденить
	void expellStudent(const size_t&);
	std::string getTitle() const;
	std::shared_ptr<Student> getHead();
	size_t getStudentsCount() const;
	std::shared_ptr<Student> getStudent(const size_t& i);
};


#endif