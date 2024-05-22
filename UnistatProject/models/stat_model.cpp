#include <iostream>
#include <fstream>
#include <string>
#include "stat_model.h"
#include "../helpers/text.h"
using namespace std;

string to_frecord(stat_record record, string sep)
{
	string stat_frecord = record.id + ";" + record.surname + ";" + record.first_name + ";" + record.patronymic + ";";
	for (int grade : record.grades)
	{
		stat_frecord += to_string(grade) + ";";
	}
	return stat_frecord;
}

void delete_frecord_id(fm::file_model fmodel, string id)
{
	string temp_filename = "delete_records_temp.txt";
	ifstream input_file(fm::get_fmodel_path(fmodel));
	ofstream temp_file(temp_filename);

	if (!input_file.is_open())
	{
		throw exception("Ошибка. Файл ведомости абитуриентов не найден!");
	}

	if (!temp_file.is_open())
	{
		throw exception("Ошибка. Временный файл удаления записей ведомости не найден!");
	}

	string line;
	bool is_found = false;

	while (getline(input_file, line))
	{
		if (line.empty())
		{
			continue;
		}
		int end_id_index = line.find(';');
		if (end_id_index == -1)
		{
			throw invalid_argument("Ошибка. Неверный формат строки данных ведомости!");
		}

		string record_id = line.substr(0, end_id_index);
		if (id == record_id)
		{
			is_found = true;
			continue;
		}

		temp_file << line << endl;
	}

	input_file.close();
	temp_file.close();
	cout << is_found;

	if (is_found)
	{
		remove(fmodel.filename.c_str());
		rename(temp_filename.c_str(), fmodel.filename.c_str());
	}
	else
	{
		remove(temp_filename.c_str());
	}
}

void create_frecord(fm::file_model file_model, fm::file_model index_model, stat_record record)
{
	string index_path = fm::get_fmodel_path(index_model);
	ifstream index_file(index_path);
	if (!index_file.is_open())
	{
		throw exception("Ошибка. Файл индекса ведомости абитуриентов не найден!");
	}

	string line;
	getline(index_file, line);
	index_file.close();

	string frecord_id = add_num(line);
	if (frecord_id == "")
	{
		throw exception("Ошибка. Не удалось преобразовать индекс ведомости абитуриентов!");
	}
	record.id = frecord_id;

	ofstream output_index_file(index_path, ios::trunc);
	if (!output_index_file.is_open())
	{
		throw exception("Ошибка. Файл индекса ведомости абитуриентов не найден!");
	}
	output_index_file << frecord_id;
	output_index_file.close();

	ofstream output_file(fm::get_fmodel_path(file_model), ios::app);
	if (!output_file.is_open())
	{
		throw exception("Ошибка. Файл ведомости абитуриентов не найден!");
	}
	string frecord = to_frecord(record) + "\n";
	output_file << frecord;
	output_file.close();
}