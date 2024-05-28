#include <iostream>
#include <map>
#include <Windows.h>
#include "helpers/console.h"
#include "settings.h"
#include "pages/load_page.h"
#include "pages/start_page.h"
#include "pages/tutorial_page.h"
#include "pages/stat/stat_page.h"
#include "pages/stat/stat_record_page.h"
#include "pages/settings_page.h"
#include "visual/colors.h"
#include "visual/dialogs.h"
#include "models/stat_model.h"
#include "models/file_model.h"
#include "controllers/stat_record.h"
using namespace std;
using namespace setting;

int main()
{
	setlocale(LC_ALL, "RuS");
	SetConsoleCP(1251);
	
	try
	{
		read_settings();
		fm::set_fmodel("students_list.txt");
		fm::set_index_model("index.txt");
	}
	catch (exception e)
	{
		error_dialog(e.what());
		return 0;
	}

	show_console_cursor(false);

	cr::read_active_colors();

	if (get_parameter("showLoading") == "true")
	{
		show_load_page();
		clear_console();
	}

	if (get_parameter("showTutorial") == "true")
	{
		show_console_cursor(true);
		show_tutorial_page();
		show_console_cursor(false);
	}

	string action = app_action::start_page;
	while (true)
	{
		if (action == app_action::start_page)
		{
			action = show_start_page();
			continue;
		}
		if (action == app_action::settings_page)
		{
			action = show_settings_page();
			continue;
		}
		if (action == app_action::stats_page)
		{
			action = show_stat_page();
			continue;
		}
		if (action == app_action::stats_record_page)
		{
			action = show_stat_record_page(stat_record_controller::get_active_record());
			continue;
		}
		if (action == app_action::create_stats_record_page)
		{
			action = show_create_stat_record_page();
			continue;
		}
		if (action == app_action::exit_app)
		{
			clear_console();
			set_position(0, 0);
			setting::save_settings();
			return 0;
		}
	}
}
