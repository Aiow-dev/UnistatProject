﻿#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "console.h"
#include "student.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RuS");

	show_console_cursor(false);

	set_position(1, 1);
	cout << "Добро пожаловать, пользователь!" << endl;
	set_position(1, 2);
	cout << "Для навигации в приложении используйте стрелки клавиатуры" << endl;
	set_position(1, 3);
	cout << "__________________________________________________________________" << endl;
	set_position(1, 4);
	cout << "Меню:" << endl;
	string main_points[] = {
		"1. Ведомость абитуриентов",
		"2. Список абитуриентов (балл выше среднего)",
		"3. Создание записи",
		"4. Поиск записи",
		"5. Выход"
	};
	int selected_point = menu(5, main_points, 1, 6);

	clear_console();

	try
	{
		vector<student> node_list = read_student_stat("students_list.txt");
		for (student node : node_list)
		{
			for (int grade : node.grades) {
				cout << grade << " ";
			}
			cout << endl;
		}
	}
	catch (exception e)
	{
		cout << e.what();
		return 0;
	}

	return 0;
}
