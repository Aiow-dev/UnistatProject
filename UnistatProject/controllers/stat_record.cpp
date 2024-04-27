#include <iostream>
#include "../models/stat_model.h"
using namespace std;

namespace stat_record_controller
{
	stat_record _active_record{};
	stat_record get_active_record()
	{
		return _active_record;
	}

	void set_active_record(stat_record record)
	{
		_active_record = record;
	}
}