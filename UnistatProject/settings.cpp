#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include "helpers/text.h"
using namespace std;

namespace setting
{
	map<string, string> _settings{};

	string get_parameter(string parameter)
	{
		return _settings[parameter];
	}

	void set_parameter(string parameter, string value)
	{
		_settings[parameter] = value;
	}

	void read_settings()
	{
		ifstream file("settings.txt");
		if (!file.is_open())
		{
			throw exception("Ошибка. Файл настроек не найден!");
		}

		map<string, string> parameters;

		string line;
		while (getline(file, line))
		{
			int sep_index = line.find(':');
			if (sep_index != -1)
			{
				int line_len = line.length();
				string key = trim(line.substr(0, sep_index));
				string value = trim(line.substr(sep_index + 1));
				parameters[key] = value;
			}
		}

		file.close();

		_settings = parameters;
	}

	void save_settings()
	{
		ofstream file("settings.txt");
		if (!file.is_open())
		{
			throw exception("Ошибка. Файл настроек не найден!");
		}

		for (pair<string, string> parameter : _settings)
		{
			file << parameter.first << " : " << parameter.second << endl;
		}

		file.close();
	}
}
