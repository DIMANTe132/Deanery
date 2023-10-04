#include "deanery.h"
#include <iostream> // Излишние включения


int main()
{
	Deanery deanery;
	int x;
	while (true)
	{
		std::cout << "What are you want to do?" << std::endl;
		std::cout << "(1) Add random marks" << std::endl;
		std::cout << "(2) Select Head" << std::endl; // Опечатка
		std::cout << "(3) Expell students" << std::endl;
		std::cout << "(4) Change group" << std::endl;
		std::cout << "(5) Print data" << std::endl;
		std::cout << "(6) Statistics" << std::endl;
		std::cout << "(7) Save" << std::endl;
		std::cout << "(0) Exit" << std::endl;
		std::cin >> x;
		system("cls"); // Дублирование кода
		switch (x)
		{
		case 1:
			deanery.addRandomMarks();
			break;
		case 2:
			deanery.selectHead();
			break;
		case 3:
			deanery.expellStudents();
			break;
		case 4:
			deanery.changeGroup();
			break;
		case 5:
			deanery.printData();
			break;
		case 6:
			deanery.statistics();
			break;
		case 7:
			deanery.save();
			break;
		case 0:
			return 0;
		default:
			std::cout << "This command does not exist!" << std::endl;
			break;
		}
		std::cout << std::endl; // Дублирование кода
	}
}