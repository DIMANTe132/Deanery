#include <iostream>
#include "deanery.h"
#include "group.h"
#include "student.h"


int main()
{
	setlocale(LC_ALL, "");
	Deanery deanery;
	int x;
	while (true)
	{
		std::cout << "What are you want to do?" << std::endl;
		std::cout << "(1) Add random marks" << std::endl;
		std::cout << "(2) Elect Head" << std::endl;
		std::cout << "(3) Expell students" << std::endl;
		std::cout << "(4) Change group" << std::endl;
		std::cout << "(5) Print data" << std::endl;
		std::cout << "(6) Statistics" << std::endl;
		std::cout << "(7) Save" << std::endl;
		std::cout << "(0) Exit" << std::endl;
		std::cin >> x;
		switch (x)
		{
		case 1:
			system("cls");
			deanery.addRandomMarks();
			std::cout << std::endl;
			break;
		case 2:
			system("cls");
			deanery.selectHead();
			std::cout << std::endl;
			break;
		case 3:
			system("cls");
			deanery.expellStudents();
			std::cout << std::endl;
			break;
		case 4:
			system("cls");
			deanery.changeGroup();
			std::cout << std::endl;
			break;
		case 5:
			system("cls");
			deanery.printData();
			std::cout << std::endl;
			break;
		case 6:
			system("cls");
			deanery.statistics();
			std::cout << std::endl;
			break;
		case 7:
			system("cls");
			deanery.save();
			std::cout << std::endl;
			break;
		case 0:
			return 0;
		default:
			system("cls");
			std::cout << "This command does not exist!" << std::endl;
			std::cout << std::endl;
			break;
		}
	}
}