#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "student.h"
#include "person.h"
using namespace std;

student to_stud_stat_node(string stud_stat_data, string sep = ";")
{
	student node;
	person person;
	int grades[4]{};
	for (int i = 0; i < 7; i++)
	{
		int sep_index = stud_stat_data.find(sep);
		int num_delete = sep_index + 1;
		string node_part = stud_stat_data.substr(0, sep_index);
		stud_stat_data.erase(0, num_delete);

		if (i == 0)
		{
			person.surname = node_part;
		}
		if (i == 1)
		{
			person.first_name = node_part;
		}
		if (i == 2)
		{
			person.patronymic = node_part;
		}
		if (i > 2)
		{
			grades[i - 3] = stoi(node_part);
		}
	}
	node.person = person;
	node.grades[0] = grades[0];
	node.grades[1] = grades[1];
	node.grades[2] = grades[2];
	node.grades[3] = grades[3];
	return node;
}

vector<student> read_student_stat(string filepath)
{
	vector<student> node_list{};
	ifstream student_stat(filepath);
	if (student_stat.is_open())
	{
		string line;
		int line_index = 0;
		while (getline(student_stat, line))
		{
			node_list.push_back(to_stud_stat_node(line));
			line_index++;
		}
	}
	return node_list;
}

