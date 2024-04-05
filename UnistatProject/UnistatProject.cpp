#include <iostream>
#include <map>
#include "console.h"
#include "settings.h"
#include "load.h"
#include "start.h"
#include "tutorial_page.h"
#include "colors.h"
using namespace std;
using namespace setting;

int main()
{
	setlocale(LC_ALL, "RuS");
	
	try
	{
		read_settings();
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

	show_start_menu();

	return 0;
}
