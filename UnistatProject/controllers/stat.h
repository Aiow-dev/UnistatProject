#pragma once
#include <iostream>
#include <vector>
#include "../models/stat_model.h"
using namespace std;

stat_record to_stat_record(string data, string sep = ";");
vector<stat_record> read_student_stat(fm::file_model fmodel);
void delete_record_id(vector<stat_record> records, string id);
double get_record_grades_avg(stat_record record);
double get_records_grades_avg(vector<stat_record> records);
vector<stat_record> slice_records(vector<stat_record> records, int from, int to);
