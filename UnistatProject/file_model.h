#pragma once
#include <iostream>
using namespace std;

namespace fm
{
	struct file_model
	{
		string path;
		string filename;
	};

	extern file_model _fmodel;

	void set_fmodel(string filename, string path=".\\");
	file_model get_fmodel();
	string get_fmodel_path(file_model fmodel);
}
