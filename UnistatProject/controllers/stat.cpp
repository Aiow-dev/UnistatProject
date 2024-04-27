#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "../controllers/stat.h"
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

double get_records_grades_avg(vector<stat_record> records)
{
	double sum = 0;
	for (stat_record record : records)
	{
		double current_avg = get_record_grades_avg(record);
		sum += current_avg;
	}

	return sum / records.size();
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
