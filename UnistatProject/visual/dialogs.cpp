#include <iostream>
#include <conio.h>
#include "../helpers/console.h"
#include "colors.h"
#include "../models/stat_model.h"
#include "../models/file_model.h"
using namespace std;

void show_frame_line(int start_x, int start_y, int length)
{
	set_position(start_x, start_y);
	cout << "+" << string(length - 2, '-') << "+";
}

void show_dialog_header(int start_x, int end_x, int start_y, string title)
{
	int max_header_width = end_x - start_x - 4;
	int margin_content_x = (max_header_width - title.length()) / 2;
	int content_middle = start_x + margin_content_x + 2;

	show_frame_line(start_x, start_y, end_x - start_x + 1);
	set_position(start_x, start_y + 1);
	cout << "|";
	set_position(end_x, start_y + 1);
	cout << "|";
	set_position(start_x, start_y + 2);
	cout << "|";
	set_position(end_x, start_y + 2);
	cout << "|";
	set_position(content_middle, start_y + 2);
	set_console_color(cr::fg_active_text, cr::black);
	cout << title;
	set_console_color(cr::light_gray, cr::black);
	set_position(start_x, start_y + 3);
	cout << "|";
	set_position(end_x, start_y + 3);
	cout << "|";
	show_frame_line(start_x, start_y + 4, end_x - start_x + 1);
}

void show_dialog_content_frame(int start_x, int end_x, int start_y, int frame_height)
{
	for (int i = 0; i < frame_height; i++)
	{
		set_position(start_x, start_y);
		cout << "|";
		set_position(end_x, start_y);
		cout << "|";
		start_y++;
	}

	show_frame_line(start_x, start_y, end_x - start_x + 1);
}

bool question_dialog(string title, string content)
{
	clear_console();
	show_console_cursor(true);

	int content_max_width = 54;
	int content_len = content.length();
	int content_height = (content_len / content_max_width) + (content_len % content_max_width > 0);
	int frame_height = content_height + 4;
	int margin_dialog_y = (25 - frame_height) / 2;

	show_dialog_header(30, 88, margin_dialog_y, title);
	show_dialog_content_frame(30, 88, margin_dialog_y + 5, frame_height);

	int content_max_x = 86;
	int current_content_x = 32;
	int current_content_y = margin_dialog_y + 6;

	set_position(current_content_x, current_content_y);

	for (int i = 0; i < content_len; i++)
	{
		if (current_content_x > content_max_x)
		{
			current_content_x = 32;
			current_content_y++;
			set_position(current_content_x, current_content_y);
		}
		cout << content[i];
		current_content_x++;
	}

	int button_y = current_content_y + 2;
	set_console_color(cr::black, cr::light_red);
	set_position(45, button_y);
	cout << "[Да]";
	set_console_color(cr::black, cr::light_gray);
	set_position(68, button_y);
	cout << "[Нет]";
	set_console_color(cr::light_gray, cr::black);

	int current_btn = 1;
	bool is_confirm = false;

	while (true)
	{
		int key_input = _getch();

		if (key_input == 75 && current_btn > 0)
		{
			set_position(49, button_y);
			current_btn--;
		}
		if (key_input == 77 && current_btn < 2)
		{
			set_position(73, button_y);
			current_btn++;
		}
		if (key_input == '\r')
		{
			is_confirm = current_btn == 0;
			break;
		}
		if (key_input == 27)
		{
			is_confirm = false;
			break;
		}
	}

	clear_console();
	show_console_cursor(false);

	return is_confirm;
}