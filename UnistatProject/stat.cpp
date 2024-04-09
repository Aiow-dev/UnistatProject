#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "stat.h"
using namespace std;

stat_node to_stat_node(string data, string sep)
{
	stat_node node;

	for (int i = 0; i < 8; i++)
	{
		int sep_index = data.find(sep);

		if (sep_index == -1)
		{
			throw invalid_argument("Ошибка. Неверный формат строки данных ведомости!");
		}

		int num_delete = sep_index + 1;
		string node_part = data.substr(0, sep_index);
		data.erase(0, num_delete);

		switch (i)
		{
		case 0: node.id = stoi(node_part);
			break;
		case 1: node.surname = node_part;
			break;
		case 2: node.first_name = node_part;
			break;
		case 3: node.patronymic = node_part;
			break;
		}

		if (i > 3)
		{
			node.grades[i - 4] = stoi(node_part);
		}
	}

	return node;
}

vector<stat_node> read_student_stat(string filepath)
{
	ifstream student_stat(filepath);

	if (student_stat.is_open())
	{
		vector<stat_node> node_list{};
		string line;
		int line_index = 0;

		while (getline(student_stat, line))
		{
			try
			{
				node_list.push_back(to_stat_node(line));
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

double get_node_grades_avg(stat_node node)
{
	return (node.grades[0] + node.grades[1] + node.grades[2] + node.grades[3]) / 4.0;
}

double get_nodes_grades_avg(vector<stat_node> nodes)
{
	double sum = 0;
	for (stat_node node : nodes)
	{
		double current_avg = get_node_grades_avg(node);
		sum += current_avg;
	}

	return sum / nodes.size();
}

vector<stat_node> slice_nodes(vector<stat_node> nodes, int from, int to)
{
	int size = nodes.size();
	if (from > size - 1)
	{
		return vector<stat_node>();
	}
	if (to > size - 1)
	{
		return vector<stat_node>(nodes.begin() + from, nodes.end());
	}

	return vector<stat_node>(nodes.begin() + from, nodes.begin() + to + 1);
}
