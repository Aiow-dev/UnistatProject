#pragma once
#include <iostream>
#include <vector>
#include "person.h"
using namespace std;

struct student
{
	person person;
	int grades[4]{};
};

vector<student> read_student_stat(string filepath);
