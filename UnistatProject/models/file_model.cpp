#include <iostream>
#include "file_model.h"
using namespace std;

namespace fm
{
	file_model _fmodel{};
	file_model _index_model{};

	void set_fmodel(string filename, string path)
	{
		if (filename.empty())
		{
			throw exception("Имя файла не может быть пустым!");
		}

		_fmodel.filename = filename;
		_fmodel.path = path;
	}

	file_model get_fmodel()
	{
		return _fmodel;
	}

	void set_index_model(string filename, string path)
	{
		if (filename.empty())
		{
			throw exception("Имя файла не может быть пустым!");
		}

		_index_model.filename = filename;
		_index_model.path = path;
	}

	file_model get_index_model()
	{
		return _index_model;
	}

	string get_fmodel_path(file_model fmodel)
	{
		return fmodel.path + fmodel.filename;
	}
}