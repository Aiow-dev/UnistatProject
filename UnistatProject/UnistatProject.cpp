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

	int start_page_point = show_start_page();
	clear_console();
	switch (start_page_point)
	{
	case 0: show_stat_page();
		break;
	case 2: return 0;
	}

	return 0;
}
