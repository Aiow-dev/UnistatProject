#include <iostream>
#include <map>
#include "console.h"
#include "settings.h"
#include "load.h"
#include "start_page.h"
#include "tutorial_page.h"
#include "colors.h"
#include "stat_page.h"
#include "stat_model.h"
#include "file_model.h"
#include "stat_record_page.h"
using namespace std;
using namespace setting;

int main()
{
	setlocale(LC_ALL, "RuS");
	
	try
	{
		read_settings();
		fm::set_fmodel("students_list.txt");
	}
	catch (exception e)
	{
		cout << e.what();
		return 0;
	}

	show_console_cursor(false);

	cr::read_active_colors();

	if (get_parameter("showLoading") == "true")
	{
		show_loading();
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
		if (action == app_action::stats_page)
		{
			action = show_stat_page();
			continue;
		}
		if (action == app_action::stats_record_page)
		{
			action = stat_record_page::show_stat_record_page(stat_record_page::get_active_record());
			continue;
		}
		if (action == app_action::exit_app)
		{
			clear_console();
			set_position(0, 0);
			return 0;
		}
	}
}
