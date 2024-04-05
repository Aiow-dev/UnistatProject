#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct student
{
	string surname;
	string first_name;
	string patronymic;
	double avg_grade;
	int grades[4]{};
};

vector<student> read_student_stat(string filepath);
