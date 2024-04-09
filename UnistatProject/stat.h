#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct stat_node
{
	int id;
	string surname;
	string first_name;
	string patronymic;
	int grades[4]{};
};

stat_node to_stat_node(string data, string sep = ";");
vector<stat_node> read_student_stat(string filepath);
double get_node_grades_avg(stat_node node);
double get_nodes_grades_avg(vector<stat_node> nodes);
vector<stat_node> slice_nodes(vector<stat_node> nodes, int from, int to);
