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

struct find_params
{
	string parameter;
	string value;
};

struct filter_params
{
	string parameter;
	string value_parameter;
	string value;
	bool comparison;
};

struct sort_params
{
	string function;
	string parameter;
	bool order;
};

string to_frecord(stat_record record, string sep = ";");
void delete_frecord_id(fm::file_model fmodel, string id);
void create_frecord(fm::file_model fmodel, fm::file_model index_model, stat_record record);
