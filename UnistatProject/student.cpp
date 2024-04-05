#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "student.h"
using namespace std;

student to_stud_stat_node(string stud_stat_data, string sep = ";")
{
	student node;

	for (int i = 0; i < 7; i++)
	{
		int sep_index = stud_stat_data.find(sep);

		if (sep_index == -1)
		{
			throw invalid_argument("Ошибка. Неверный формат строки данных ведомости!");
		}

		int num_delete = sep_index + 1;
		string node_part = stud_stat_data.substr(0, sep_index);
		stud_stat_data.erase(0, num_delete);

		switch (i)
		{
		case 0: node.surname = node_part;
			break;
		case 1: node.first_name = node_part;
			break;
		case 2: node.patronymic = node_part;
			break;
		}

		if (i > 2)
		{
			node.grades[i - 3] = stoi(node_part);
		}
	}

	return node;
}

vector<student> read_student_stat(string filepath)
{
	ifstream student_stat(filepath);

	if (student_stat.is_open())
	{
		vector<student> node_list{};
		string line;
		int line_index = 0;

		while (getline(student_stat, line))
		{
			try
			{
				node_list.push_back(to_stud_stat_node(line));
				line_index++;
			}
			catch (invalid_argument e)
			{
				throw e;
			}
		}

		student_stat.close();
		return node_list;
	}

	student_stat.close();
	throw exception("Ошибка. Файл ведомости абитуриентов не найден!");
}

