#include <iostream>
#include <fstream>
#include <string>
#include "file_model.h"
using namespace std;

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