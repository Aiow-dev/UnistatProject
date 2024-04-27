#pragma once
#include "../models/stat_model.h"

namespace stat_record_page
{
	extern stat_record _active_record;

	string show_stat_record_page(stat_record record);
	stat_record get_active_record();
	void set_active_record(stat_record record);
}
