#include <iostream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include "console.h"
#include "colors.h"
#include "student.h"
using namespace std;

void show_default_node(student node, int x, int y, int snm_width, int frt_width, int ptc_width)
{
	set_position(x, y);
	cout << left << setw(snm_width) << node.surname
		<< setw(frt_width) << node.first_name
		<< setw(ptc_width) << node.patronymic
		<< setw(5) << node.grades[0] << setw(5) << node.grades[1]
		<< setw(5) << node.grades[2] << setw(5) << node.grades[3]
		<< setw(12);
	set_console_color(cr::fg_active_text, cr::black);
	cout << node.avg_grade << endl;
	set_console_color(cr::light_gray, cr::black);
}

void show_active_node(student node, int x, int y, int snm_width, int frt_width, int ptc_width)
{
	set_position(x, y);
	set_console_color(cr::fg_active_marker, cr::bg_active_marker);
	cout << left << setw(snm_width) << node.surname
		<< setw(frt_width) << node.first_name
		<< setw(ptc_width) << node.patronymic
		<< setw(5) << node.grades[0] << setw(5) << node.grades[1]
		<< setw(5) << node.grades[2] << setw(5) << node.grades[3]
		<< setw(12);
	cout << node.avg_grade << endl;
	set_console_color(cr::light_gray, cr::black);
}

void show_table()
{
	try
	{
		vector<student> students = read_student_stat("students_list.txt");

		if (students.empty())
		{
			cout << "Нет записей в ведомости абитуриентов!";
			return;
		}

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

		int snm_width = max_surname_len + 5;
		int frt_width = max_first_name_len + 5;
		int ptc_width = max_patronymic_len + 5;

		set_position(20, 9);

		cout << left << setw(snm_width) << "Фамилия" << setw(frt_width) << "Имя"
			<< setw(ptc_width) << "Отчество" << setw(20) << "Отметки" << setw(12);
		set_console_color(cr::fg_active_text, cr::black);
		cout << "Средний балл" << endl;
		set_console_color(cr::light_gray, cr::black);
		set_position(20, 10);
		cout << setfill('-') << setw(snm_width) << "" << setw(frt_width) << ""
			<< setw(ptc_width) << "" << setw(32) << "" << endl;
		cout << setfill(' ');

		double sum_avg_grade = 0;
		int students_num = students.size();
		int line_y = 11;

		for (int i = 0; i < students_num; i++)
		{
			double avg_grade = (students[i].grades[0] + students[i].grades[1] + students[i].grades[2] + students[i].grades[3]) / 4.0;
			students[i].avg_grade = avg_grade;
			sum_avg_grade += avg_grade;

			show_default_node(students[i], 20, line_y, snm_width, frt_width, ptc_width);

			line_y++;
		}

		set_position(20, line_y);
		cout << setfill('-') << setw(snm_width) << "" << setw(frt_width) << ""
			<< setw(ptc_width) << "" << setw(32) << "" << endl;
		cout << setfill(' ');

		double avg_univ = sum_avg_grade / students_num;
		int table_width = snm_width + frt_width + ptc_width - 8;
		set_position(20, line_y + 1);
		cout << "Средний балл по университету" << setw(table_width) << "";
		set_console_color(cr::fg_active_text, cr::black);
		cout << avg_univ << endl;
		set_console_color(cr::light_gray, cr::black);

		int point_y = 11;
		int max_width = 87;
		int table_pointer = 0;

		show_active_node(students[0], 20, point_y, snm_width, frt_width, ptc_width);

		while (true)
		{
			int key = _getch();

			show_default_node(students[table_pointer], 20, point_y + table_pointer, snm_width, frt_width, ptc_width);

			if (key == 72)
			{
				table_pointer--;
			}
			if (key == 80)
			{
				table_pointer++;
			}

			if (table_pointer < 0)
			{
				table_pointer = 9;
			}
			if (table_pointer > 9)
			{
				table_pointer = 0;
			}

			show_active_node(students[table_pointer], 20, point_y + table_pointer, snm_width, frt_width, ptc_width);
		}
	}
	catch (invalid_argument e)
	{
		cout << e.what();
		return;
	}
}

int show_stat_page()
{
	set_position(12, 2);
	cout << "+-----------------------------------------------------------------------------------------------+";
	set_position(12, 3);
	cout << "|";
	set_position(108, 3);
	cout << "|";
	set_position(30, 4);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "Ведомость абитуриентов (вступительные экзамены в университет)";
	set_console_color(cr::light_gray, cr::black);
	set_position(12, 4);
	cout << "|";
	set_position(108, 4);
	cout << "|";
	set_position(12, 5);
	cout << "|";
	set_position(108, 5);
	cout << "|";
	set_position(12, 6);
	cout << "+-----------------------------------------------------------------------------------------------+";

	int field_y = 7;
	for (int i = 0; i < 20; i++)
	{
		set_position(12, field_y);
		cout << "|";
		set_position(108, field_y);
		cout << "|";
		field_y++;
	}
	set_position(20, field_y - 3);
	set_console_color(cr::black, cr::light_gray);
	cout << "<--";
	set_position(96, field_y - 3);
	cout << "-->";
	set_console_color(cr::light_gray, cr::black);
	set_position(12, field_y);
	cout << "+-----------------------------------------------------------------------------------------------+";

	show_table();

	return 0;
}