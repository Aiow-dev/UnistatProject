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
stat_record find_id(vector<stat_record> records, string id);
vector<stat_record> find_surname(vector<stat_record> records, string surname);
vector<stat_record> find_firstname(vector<stat_record> records, string firstname);
vector<stat_record> find_patronymic(vector<stat_record> records, string patronymic);
vector<stat_record> find_avg_grade(vector<stat_record> records, double avg_grade);
vector<stat_record> find_records(vector<stat_record> records, stat_record_find parameters);
