#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
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

vector<stat_record> find_records(vector<stat_record> records, find_params parameters)
{
	string find_parameter = parameters.parameter;

	if (find_parameter == "id")
	{
		return vector<stat_record>{find_id(records, parameters.value)};
	}
	if (find_parameter == "surname")
	{
		return find_surname(records, parameters.value);
	}
	if (find_parameter == "firstname")
	{
		return find_firstname(records, parameters.value);
	}
	if (find_parameter == "patronymic")
	{
		return find_patronymic(records, parameters.value);
	}
	if (find_parameter == "avg_grade")
	{
		try {
			return find_avg_grade(records, stod(parameters.value));
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

bool order_id(stat_record record_1, stat_record record_2)
{
	string id_1 = record_1.id;
	string id_2 = record_2.id;
	int len_id_1 = id_1.length();
	int len_id_2 = id_2.length();

	if (len_id_1 < len_id_2)
	{
		return false;
	}

	if (len_id_1 > len_id_2)
	{
		return true;
	}

	for (int i = 0; i < len_id_1; i++)
	{
		if (id_1[i] < id_2[i])
		{
			return false;
		}
	}

	return true;
}

bool order_surname(stat_record record_1, stat_record record_2)
{
	return record_1.surname[0] > record_2.surname[0];
}

bool order_firstname(stat_record record_1, stat_record record_2)
{
	return record_1.first_name[0] > record_2.first_name[0];
}

bool order_patronymic(stat_record record_1, stat_record record_2)
{
	return record_1.patronymic[0] > record_2.patronymic[0];
}

bool order_avg_grade(stat_record record_1, stat_record record_2)
{
	double avg_grade_1 = get_record_grades_avg(record_1);
	double avg_grade_2 = get_record_grades_avg(record_2);
	return avg_grade_1 > avg_grade_2;
}

vector<stat_record> sort_bubble(vector<stat_record> records, function<bool(stat_record, stat_record)> order_function, bool is_asc)
{
	int size = records.size();
	bool is_swap = false;

	for (int i = 0; i < size - 1; i++)
	{
		is_swap = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			bool order = order_function(records[j], records[j + 1]);
			if (order && is_asc)
			{
				stat_record temp = records[j];
				records[j] = records[j + 1];
				records[j + 1] = temp;
				is_swap = true;
				continue;
			}
			if (!order && !is_asc)
			{
				stat_record temp = records[j];
				records[j] = records[j + 1];
				records[j + 1] = temp;
				is_swap = true;
				continue;
			}
		}

		if (!is_swap)
		{
			break;
		}
	}

	return records;
}

void quick_partitions_asc(vector<stat_record> &records, int left, int right, function<bool(stat_record, stat_record)> order_function)
{
	stat_record pivot;
	int pivot_index;
	int l_hold = left;
	int r_hold = right;
	pivot = records[left];

	while (left < right)
	{
		while (order_function(records[right], pivot) && (left < right))
		{
			right--;
		}
		if (left != right)
		{
			records[left] = records[right];
			left++;
		}

		while (!order_function(records[left], pivot) && (left < right))
		{
			left++;
		}
		if (left != right)
		{
			records[right] = records[left];
			right--;
		}
	}

	records[left] = pivot;
	pivot_index = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot_index)
	{
		quick_partitions_asc(records, left, pivot_index - 1, order_function);
	}
	if (right > pivot_index)
	{
		quick_partitions_asc(records, pivot_index + 1, right, order_function);
	}
}

void quick_partitions_desc(vector<stat_record>& records, int left, int right, function<bool(stat_record, stat_record)> order_function)
{
	stat_record pivot;
	int pivot_index;
	int l_hold = left;
	int r_hold = right;
	pivot = records[left];

	while (left < right)
	{
		while (!order_function(records[right], pivot) && (left < right))
		{
			right--;
		}
		if (left != right)
		{
			records[left] = records[right];
			left++;
		}

		while (order_function(records[left], pivot) && (left < right))
		{
			left++;
		}
		if (left != right)
		{
			records[right] = records[left];
			right--;
		}
	}

	records[left] = pivot;
	pivot_index = left;
	left = l_hold;
	right = r_hold;
	if (left < pivot_index)
	{
		quick_partitions_desc(records, left, pivot_index - 1, order_function);
	}
	if (right > pivot_index)
	{
		quick_partitions_desc(records, pivot_index + 1, right, order_function);
	}
}

vector<stat_record> sort_quick(vector<stat_record> records, function<bool(stat_record, stat_record)> order_function, bool is_asc)
{
	int size = records.size();

	if (is_asc)
	{
		quick_partitions_asc(records, 0, size - 1, order_function);
	}
	else
	{
		quick_partitions_desc(records, 0, size - 1, order_function);
	}

	return records;
}

sort_result sort_records(vector<stat_record> records, sort_params parameters)
{
	function<bool(stat_record, stat_record)> order_function = order_id;
	string sort_parameter = parameters.parameter;
	if (sort_parameter == "surname")
	{
		order_function = order_surname;
	}
	else if (sort_parameter == "firstname")
	{
		order_function = order_firstname;
	}
	else if (sort_parameter == "patronymic")
	{
		order_function = order_patronymic;
	}
	else if (sort_parameter == "avg_grade")
	{
		order_function = order_avg_grade;
	}

	function<vector<stat_record>(vector<stat_record>, function<bool(stat_record, stat_record)>, bool)> sort_function = sort_bubble;
	string function = parameters.function;
	if (function == "quick")
	{
		sort_function = sort_quick;
	}

	auto t1 = std::chrono::high_resolution_clock::now();
	
	records = sort_function(records, order_function, parameters.order);

	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_double = t2 - t1;

	return sort_result{ ms_double.count(), records};
}
