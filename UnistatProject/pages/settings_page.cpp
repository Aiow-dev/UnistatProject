#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include "../app.h"
#include "../helpers/console.h"
#include "../visual/dialogs.h"
#include "../visual/colors.h"
#include "../settings.h"
using namespace std;

void show_color_palette(int start_x, int start_y, vector<int> colors)
{
	set_position(start_x, start_y);
	set_console_color(cr::light_gray, cr::black);
	cout << "[ ";

	int size = colors.size();

	for (int i=0;i<size - 1;i++)
	{
		set_console_color(cr::light_gray, colors[i]);
		cout << "  ";
		set_console_color(cr::light_gray, cr::black);
		cout << " ";
	}

	set_console_color(cr::light_gray, colors[size - 1]);
	cout << "  ";
	set_console_color(cr::light_gray, cr::black);
	cout << " ]";
}

string show_settings_page()
{
	clear_console();

	int frame_height = 8;
	int margin_dialog_y = (25 - frame_height) / 2;
	int header_center_x = text_to_dialog_center(30, 90, 20);

	show_dialog_header(30, 90, margin_dialog_y, "Настройки приложения");
	show_dialog_content_frame(30, 90, margin_dialog_y + 5, frame_height);

	int content_center_x = text_to_dialog_center(30, 90, 26);
	int content_y = margin_dialog_y + 6;

	set_position(content_center_x, content_y);
	cout << "Цветовая схема приложения:";
	vector<int> palette = {
		cr::blue, cr::green, cr::cyan, cr::red, cr::magenta, cr::brown, cr::light_gray,
		cr::dark_gray, cr::light_blue, cr::light_green, cr::light_cyan, cr::light_red,
		cr::light_magenta, cr::yellow , cr::white
	};
	int palette_size = palette.size();
	show_color_palette(35, content_y + 2, palette);

	int start_color_x = 37;
	int color_cursor_y = content_y + 3;

	set_position(start_color_x, color_cursor_y);
	cout << "__";

	set_position(50, color_cursor_y + 2);
	set_console_color(cr::black, cr::light_gray);
	cout << "[Закрыть настройки]";
	set_console_color(cr::light_gray, cr::black);

	int current_color = 1;
	bool is_color_changed = false;

	while (true)
	{
		int key_input = _getch();

		if (key_input == 75 && current_color > 1)
		{
			current_color--;
			is_color_changed = true;
		}
		if (key_input == 77 && current_color < palette_size)
		{
			current_color++;
			is_color_changed = true;
		}
		if (key_input == '\r' || key_input == 27)
		{
			break;
		}

		set_position(header_center_x, margin_dialog_y + 2);
		set_console_color(current_color, cr::black);
		cout << "Настройки приложения";
		set_position(start_color_x, color_cursor_y);
		cout << string(47, ' ');
		int current_color_x = start_color_x + (current_color - 1) * 3;
		set_position(current_color_x, color_cursor_y);
		cout << "__";
	}

	if (is_color_changed)
	{
		cr::fg_active_text = current_color;
		cr::bg_active_marker = current_color;

		setting::set_parameter("fgActiveTextColor", to_string(current_color));
		setting::set_parameter("bgActiveMarkerColor", to_string(current_color));
	}

	set_console_color(cr::light_gray, cr::black);
	clear_console();

	return app_action::start_page;
}