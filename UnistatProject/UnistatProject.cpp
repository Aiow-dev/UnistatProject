#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "console.h"
#include "student.h"
#include "stat.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RuS");

	int columns_pos = get_console_columns() / 2;
	int rows_pos = get_console_rows() / 2;

	show_console_cursor(false);

	set_position(1, 1);
	cout << "Добро пожаловать, пользователь!" << endl;
	set_position(1, 2);
	cout << "Для навигации в приложении используйте стрелки или цифры клавиатуры" << endl;
	set_position(columns_pos, rows_pos - 6);
	cout << "Меню" << endl;
	set_position(columns_pos - 20, rows_pos - 5);
	cout << "-------------------------------------------" << endl;

	string main_points[] = {
		"1. Ведомость абитуриентов",
		"2. Список абитуриентов (балл выше среднего)",
		"3. Создание записи",
		"4. Поиск записи",
		"5. Выход"
	};
	int selected_point = menu(5, main_points, columns_pos - 20, rows_pos - 4);

	clear_console();

	try
	{
		if (selected_point == 0)
		{
			show_stat_table();
		}
	}
	catch (exception e)
	{
		cout << e.what();
		return 0;
	}

	return 0;
}
