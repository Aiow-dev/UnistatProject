#pragma once
#include <iostream>
#include <map>
using namespace std;

namespace setting
{
	extern map<string, string> _settings;

	string get_parameter(string parameter);
	void set_parameter(string parameter, string value);
	void read_settings();
	void save_settings();
}

