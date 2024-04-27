#pragma once
#include <iostream>
#include "file_model.h"
using namespace std;

struct stat_record
{
	string id;
	string surname;
	string first_name;
	string patronymic;
	int grades[4]{};
};

void delete_frecord_id(fm::file_model fmodel, string id);
