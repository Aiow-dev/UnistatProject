#include <iostream>
#include <conio.h>
#include <iomanip>
#include "../helpers/console.h"
#include "../visual/colors.h"
#include "../visual/dialogs.h"
#include "../app.h"
using namespace std;

string show_start_page()
{
	show_dialog_header(30, 88, 9, "Выберите действие");
	show_dialog_content_frame(30, 88, 14, 5);

	string menu_items[] = {
		"[1] Открыть ведомость абитуриентов",
		"[2] Открыть настройки",
		"[3] Выйти из приложения"
	};

	set_position(43, 15);
	set_console_color(cr::fg_active_marker, cr::bg_active_marker);
	cout << menu_items[0];
	set_console_color(cr::light_gray, cr::black);
	set_position(43, 16);
	cout << menu_items[1];
	set_position(43, 17);
	cout << menu_items[2];

	int menu_y = 15;
	int max_width = menu_items[0].length();
	int menu_pointer = 0;

	while (true)
	{
		int key = _getch();

		set_position(43, menu_y + menu_pointer);
		cout << left << setw(max_width) << menu_items[menu_pointer];

		if (key == 72)
		{
			menu_pointer--;
		}
		if (key == 80)
		{
			menu_pointer++;
		}
		if (key >= 49 && key <= 51)
		{
			int digit = key - '0';
			menu_pointer = digit - 1;
		}
		if (key == '\r')
		{
			break;
		}

		if (menu_pointer < 0)
		{
			menu_pointer = 2;
		}
		if (menu_pointer > 2)
		{
			menu_pointer = 0;
		}

		set_position(43, menu_y + menu_pointer);
		set_console_color(cr::fg_active_marker, cr::bg_active_marker);
		cout << left << setw(max_width) << menu_items[menu_pointer];
		set_console_color(cr::light_gray, cr::black);
	}

	switch (menu_pointer)
	{
	case 0: return app_action::stats_page;
	case 1: return app_action::settings_page;
	case 2: return app_action::exit_app;
	}
}