#pragma once
#include "../models/stat_model.h"

namespace stat_record_controller
{
	extern stat_record _active_record;

	stat_record get_active_record();
	void set_active_record(stat_record record);
}