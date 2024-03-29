#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "student.h"
#include "start.h"
#include <Windows.h>
#include "console.h"
using namespace std;

void show_stat_menu()
{
	set_position(0, 3);
	cout << "Меню:" << endl;
	string menu_points[] = {
		"[1] Сортировать в порядке убывания среднего балла",
		"[2] Сортировать в порядке возрастания среднего балла",
		"[3] Назад"
	};
	int selected_point = menu(3, menu_points, 0, 4, 52);
	clear_console();

	if (selected_point == 2)
	{
		show_start_menu();
	}
}

void show_stat_table()
{
	vector<student> students = read_student_stat("students_list.txt");

	if (students.empty())
	{
		cout << "Нет записей в ведомости абитуриентов!";
		return;
	}

	cout << "Ведомость абитуриентов (вступительные экзамены в университет)" << endl;
	set_position(0, 9);

	int max_surname_len = 0;
	int max_first_name_len = 0;
	int max_patronymic_len = 0;

	for (student student : students)
	{
		int st_surname_len = student.surname.length();
		int st_first_name_len = student.first_name.length();
		int st_patronymic_len = student.patronymic.length();

		if (max_surname_len < st_surname_len)
		{
			max_surname_len = st_surname_len;
		}
		if (max_first_name_len < st_first_name_len)
		{
			max_first_name_len = st_first_name_len;
		}
		if (max_patronymic_len < st_patronymic_len)
		{
			max_patronymic_len = st_patronymic_len;
		}
	}

	int surname_column = max_surname_len + 5;
	int first_name_column = max_first_name_len + 5;
	int patronymic_column = max_patronymic_len + 5;

	cout << left << setw(surname_column) << "Фамилия" << setw(first_name_column) << "Имя"
		<< setw(patronymic_column) << "Отчество" << setw(20) << "Отметки" << setw(12);
	set_console_color(3, 0);
	cout << "Средний балл" << endl;
	set_console_color(7, 0);
	cout << setfill('-') << setw(surname_column) << "" << setw(first_name_column) << ""
		<< setw(patronymic_column) << "" << setw(32) << "" << endl;
	cout << setfill(' ');

	double sum_avg_grade = 0;
	int students_num = students.size();

	for (int i=0; i<students_num;i++)
	{
		double avg_grade = (students[i].grades[0] + students[i].grades[1] + students[i].grades[2] + students[i].grades[3]) / 4.0;
		sum_avg_grade += avg_grade;

		cout << left << setw(surname_column) << students[i].surname
			<< setw(first_name_column) << students[i].first_name
			<< setw(patronymic_column) << students[i].patronymic
			<< setw(5) << students[i].grades[0] << setw(5) << students[i].grades[1]
			<< setw(5) << students[i].grades[2] << setw(5) << students[i].grades[3]
			<< setw(5);
		set_console_color(3, 0);
		cout << avg_grade << endl;
		set_console_color(7, 0);
	}

	cout << setfill('-') << setw(surname_column) << "" << setw(first_name_column) << ""
		<< setw(patronymic_column) << "" << setw(32) << "" << endl;
	cout << setfill(' ');

	double avg_univ = sum_avg_grade / students_num;
	int table_width = surname_column + first_name_column + patronymic_column - 8;
	cout << "Средний балл по университету" << setw(table_width) << "";
	set_console_color(3, 0);
	cout << avg_univ << endl;
	set_console_color(7, 0);

	show_stat_menu();
}