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
	extern file_model _index_model;

	void set_fmodel(string filename, string path=".\\");
	file_model get_fmodel();
	void set_index_model(string filename, string path = ".\\");
	file_model get_index_model();
	string get_fmodel_path(file_model fmodel);
}
