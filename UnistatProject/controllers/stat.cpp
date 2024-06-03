#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "stat.h"
using namespace std;

stat_record to_stat_record(string data, string sep)
{
	stat_record record;

	for (int i = 0; i < 8; i++)
	{
		int sep_index = data.find(sep);

		if (sep_index == -1)
		{
			throw invalid_argument("Ошибка. Неверный формат строки данных ведомости!");
		}

		int num_delete = sep_index + 1;
		string node_part = data.substr(0, sep_index);
		data.erase(0, num_delete);

		switch (i)
		{
		case 0: record.id = node_part;
			break;
		case 1: record.surname = node_part;
			break;
		case 2: record.first_name = node_part;
			break;
		case 3: record.patronymic = node_part;
			break;
		}

		if (i > 3)
		{
			record.grades[i - 4] = stoi(node_part);
		}
	}

	return record;
}

vector<stat_record> read_student_stat(fm::file_model fmodel)
{
	ifstream student_stat(fm::get_fmodel_path(fmodel));

	if (student_stat.is_open())
	{
		vector<stat_record> stat_records{};
		string line;
		int line_index = 0;

		while (getline(student_stat, line))
		{
			if (line.empty())
			{
				continue;
			}
			try
			{
				stat_records.push_back(to_stat_record(line));
				line_index++;
			}
			catch (invalid_argument e)
			{
				throw e;
			}
		}

		student_stat.close();
		return stat_records;
	}

	student_stat.close();
	throw exception("Ошибка. Файл ведомости абитуриентов не найден!");
}

void delete_record_id(vector<stat_record> records, string id)
{
	int find_index = -1;

	for (int i = 0; i < records.size(); i++)
	{
		if (records[i].id == id)
		{
			find_index = i;
		}
	}

	if (find_index != -1)
	{
		records.erase(records.begin() + find_index);
	}
}

double get_record_grades_avg(stat_record record)
{
	return (record.grades[0] + record.grades[1] + record.grades[2] + record.grades[3]) / 4.0;
}

double get_records_grades_avgmin(vector<stat_record> records)
{
	int size = records.size();

	if (size == 0)
	{
		return 0;
	}

	double min = get_record_grades_avg(records[0]);
	for (int i = 1; i < size; i++)
	{
		double current_avg = get_record_grades_avg(records[i]);
		if (min > current_avg)
		{
			min = current_avg;
		}
	}

	return min;
}

double get_records_grades_avg(vector<stat_record> records)
{
	int size = records.size();

	if (size == 0)
	{
		return 0;
	}

	double sum = 0;
	for (stat_record record : records)
	{
		double current_avg = get_record_grades_avg(record);
		sum += current_avg;
	}

	return sum / size;
}

double get_records_grades_avgmax(vector<stat_record> records)
{
	int size = records.size();

	if (size == 0)
	{
		return 0;
	}

	double max = get_record_grades_avg(records[0]);
	for (int i = 1; i < size; i++)
	{
		double current_avg = get_record_grades_avg(records[i]);
		if (max < current_avg)
		{
			max = current_avg;
		}
	}

	return max;
}

vector<stat_record> slice_records(vector<stat_record> records, int from, int to)
{
	int size = records.size();
	if (from > size - 1)
	{
		return vector<stat_record>();
	}
	if (to > size - 1)
	{
		return vector<stat_record>(records.begin() + from, records.end());
	}

	return vector<stat_record>(records.begin() + from, records.begin() + to + 1);
}

stat_record find_id(vector<stat_record> records, string id)
{
	stat_record find_record{};
	
	for (stat_record record : records)
	{
		if (record.id == id)
		{
			find_record = record;
			break;
		}
	}

	return find_record;
}

vector<stat_record> find_surname(vector<stat_record> records, string surname)
{
	vector<stat_record> find_records{};

	for (stat_record record : records)
	{
		if (record.surname == surname)
		{
			find_records.push_back(record);
		}
	}

	return find_records;
}

vector<stat_record> find_firstname(vector<stat_record> records, string firstname)
{
	vector<stat_record> find_records{};

	for (stat_record record : records)
	{
		if (record.first_name == firstname)
		{
			find_records.push_back(record);
		}
	}

	return find_records;
}

vector<stat_record> find_patronymic(vector<stat_record> records, string patronymic)
{
	vector<stat_record> find_records{};

	for (stat_record record : records)
	{
		if (record.patronymic == patronymic)
		{
			find_records.push_back(record);
		}
	}

	return find_records;
}

vector<stat_record> find_avg_grade(vector<stat_record> records, double avg_grade)
{
	vector<stat_record> find_records{};

	for (stat_record record : records)
	{
		double record_avg_grade = get_record_grades_avg(record);
		if (record_avg_grade == avg_grade)
		{
			find_records.push_back(record);
		}
	}

	return find_records;
}

vector<stat_record> find_records(vector<stat_record> records, stat_record_find parameters)
{
	string find_parameter = parameters.find_parameter;

	if (find_parameter == "id")
	{
		return vector<stat_record>{find_id(records, parameters.find_value)};
	}
	if (find_parameter == "surname")
	{
		return find_surname(records, parameters.find_value);
	}
	if (find_parameter == "firstname")
	{
		return find_firstname(records, parameters.find_value);
	}
	if (find_parameter == "patronymic")
	{
		return find_patronymic(records, parameters.find_value);
	}
	if (find_parameter == "avg_grade")
	{
		try {
			return find_avg_grade(records, stod(parameters.find_value));
		}
		catch (exception e)
		{
			return vector<stat_record>{};
		}
	}

	return vector<stat_record>{};
}

vector<stat_record> filter_avg_grade(vector<stat_record> records, double avg_grade, bool comparison)
{
	vector<stat_record> filter_records{};

	for (stat_record record : records)
	{
		double record_avg_grade = get_record_grades_avg(record);
		if (comparison && record_avg_grade >= avg_grade)
		{
			filter_records.push_back(record);
			continue;
		}
		if (!comparison && record_avg_grade <= avg_grade)
		{
			filter_records.push_back(record);
			continue;
		}
	}

	return filter_records;
}
