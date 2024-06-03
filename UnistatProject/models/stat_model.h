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

struct stat_record_find
{
	string find_parameter;
	string find_value;
};

struct stat_record_filter
{
	string filter_parameter;
	string filter_value_parameter;
	string filter_value;
	bool filter_comparison;
};

string to_frecord(stat_record record, string sep = ";");
void delete_frecord_id(fm::file_model fmodel, string id);
void create_frecord(fm::file_model fmodel, fm::file_model index_model, stat_record record);
