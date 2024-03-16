#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "student.h"
using namespace std;

void show_stat_table()
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

	int surname_column = max_surname_len + 5;
	int first_name_column = max_first_name_len + 5;
	int patronymic_column = max_patronymic_len + 5;

	cout << left << setw(surname_column) << "Фамилия" << setw(first_name_column) << "Имя"
		<< setw(patronymic_column) << "Отчество" << setw(10) << "Отметки" << endl;
	cout << setfill('-') << setw(surname_column) << "" << setw(first_name_column) << ""
		<< setw(patronymic_column) << "" << setw(16) << "" << endl;
	cout << setfill(' ');

	for (student student : students)
	{
		cout << left << setw(surname_column) << student.surname
			<< setw(first_name_column) << student.first_name
			<< setw(patronymic_column) << student.patronymic
			<< setw(5) << student.grades[0] << setw(5) << student.grades[1]
			<< setw(5) << student.grades[2] << setw(5) << student.grades[3]
			<< endl;
	}

	cout << setfill('-') << setw(surname_column) << "" << setw(first_name_column) << ""
		<< setw(patronymic_column) << "" << setw(16) << "" << endl;
	cout << setfill(' ');
}