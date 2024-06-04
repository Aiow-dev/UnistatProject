#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include "../models/stat_model.h"
using namespace std;

struct sort_result
{
	double time;
	vector<stat_record> records;
};

stat_record to_stat_record(string data, string sep = ";");

vector<stat_record> read_student_stat(fm::file_model fmodel);

void delete_record_id(vector<stat_record> records, string id);
double get_record_grades_avg(stat_record record);
double get_records_grades_avgmin(vector<stat_record> records);
double get_records_grades_avg(vector<stat_record> records);
double get_records_grades_avgmax(vector<stat_record> records);
vector<stat_record> slice_records(vector<stat_record> records, int from, int to);

stat_record find_id(vector<stat_record> records, string id);
vector<stat_record> find_surname(vector<stat_record> records, string surname);
vector<stat_record> find_firstname(vector<stat_record> records, string firstname);
vector<stat_record> find_patronymic(vector<stat_record> records, string patronymic);
vector<stat_record> find_avg_grade(vector<stat_record> records, double avg_grade);
vector<stat_record> find_records(vector<stat_record> records, find_params parameters);

vector<stat_record> filter_avg_grade(vector<stat_record> records, double avg_grade, bool comparison);

bool order_id(stat_record record_1, stat_record record_2);
bool order_surname(stat_record record_1, stat_record record_2);
bool order_firstname(stat_record record_1, stat_record record_2);
bool order_patronymic(stat_record record_1, stat_record record_2);
bool order_avg_grade(stat_record record_1, stat_record record_2);
vector<stat_record> sort_bubble(vector<stat_record> records, function<bool(stat_record, stat_record)> order_function, bool is_asc);
vector<stat_record> sort_quick(vector<stat_record> records, function<bool(stat_record, stat_record)> order_function, bool is_asc);
sort_result sort_records(vector<stat_record> records, sort_params parameters);
