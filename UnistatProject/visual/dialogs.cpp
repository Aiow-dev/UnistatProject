#include <iostream>
#include <conio.h>
#include "colors.h"
#include "../helpers/console.h"
#include "../models/stat_model.h"
#include "../models/file_model.h"
using namespace std;

int text_to_dialog_center(int start_x, int end_x, int text_len)
{
	int max_width = end_x - start_x - 4;
	int margin_x = (max_width - text_len) / 2;
	return start_x + margin_x + 2;
}

void show_frame_line(int start_x, int start_y, int length)
{
	set_position(start_x, start_y);
	cout << "+" << string(length - 2, '-') << "+";
}

void show_dialog_header(int start_x, int end_x, int start_y, string title)
{
	int header_center_x = text_to_dialog_center(start_x, end_x, title.length());

	show_frame_line(start_x, start_y, end_x - start_x + 1);
	set_position(start_x, start_y + 1);
	cout << "|";
	set_position(end_x, start_y + 1);
	cout << "|";
	set_position(start_x, start_y + 2);
	cout << "|";
	set_position(end_x, start_y + 2);
	cout << "|";
	set_position(header_center_x, start_y + 2);
	set_console_color(cr::fg_active_text, cr::black);
	cout << title;
	set_console_color(cr::light_gray, cr::black);
	set_position(start_x, start_y + 3);
	cout << "|";
	set_position(end_x, start_y + 3);
	cout << "|";
	show_frame_line(start_x, start_y + 4, end_x - start_x + 1);
}

void show_error_dialog_header(int start_x, int end_x, int start_y)
{
	int title_len = 6;
	int header_center_x = text_to_dialog_center(start_x, end_x, title_len);

	set_console_color(cr::light_red, cr::black);
	show_frame_line(start_x, start_y, end_x - start_x + 1);
	set_position(start_x, start_y + 1);
	cout << "|";
	set_position(end_x, start_y + 1);
	cout << "|";
	set_position(start_x, start_y + 2);
	cout << "|";
	set_position(end_x, start_y + 2);
	cout << "|";
	set_position(header_center_x, start_y + 2);
	cout << "Ошибка";
	set_position(start_x, start_y + 3);
	cout << "|";
	set_position(end_x, start_y + 3);
	cout << "|";
	show_frame_line(start_x, start_y + 4, end_x - start_x + 1);
	set_console_color(cr::light_gray, cr::black);
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

int wrap_dialog_text(int start_x, int end_x, int start_y, string text)
{
	int text_len = text.length();
	int current_x = start_x;
	int current_y = start_y;
	int wrap_count = 0;

	set_position(current_x, current_y);

	for (int i = 0; i < text_len; i++)
	{
		if (current_x > end_x)
		{
			current_x = start_x;
			current_y++;
			wrap_count++;
			set_position(current_x, current_y);
		}
		cout << text[i];
		current_x++;
	}

	return wrap_count;
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

	int wrap_content_count = wrap_dialog_text(current_content_x, content_max_x, current_content_y, content);

	int button_y = current_content_y + wrap_content_count + 2;
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

void error_dialog(string error)
{
	clear_console();
	show_console_cursor(true);

	int frame_height = 15;
	int margin_dialog_y = (25 - frame_height) / 2;

	show_error_dialog_header(30, 90, margin_dialog_y);
	set_console_color(cr::light_red, cr::black);
	show_dialog_content_frame(30, 90, margin_dialog_y + 5, frame_height);
	set_console_color(cr::light_gray, cr::black);

	int content_max_x = 88;
	int current_content_x = 32;
	int current_content_y = margin_dialog_y + 6;

	string description = "Это окно отображается, когда в приложении возникает критическая ошибка, которая приводит к "
		"завершению работы приложения. Данное окно отображает информацию о возникшей ошибке. После закрытия данного окна "
		"приложение автоматически завершит свою работу";
	int wrap_description_count = wrap_dialog_text(current_content_x, content_max_x, current_content_y, description);
	current_content_y += wrap_description_count + 2;
	set_position(current_content_x, current_content_y);
	cout << "Описание возникшей ошибки:";
	current_content_y++;
	set_position(current_content_x, current_content_y);
	wrap_dialog_text(current_content_x, content_max_x, current_content_y, error);

	set_console_color(cr::black, cr::light_gray);
	set_position(53, 23);
	cout << "[Подтвердить]";
	set_console_color(cr::light_gray, cr::black);

	while (true)
	{
		int key_input = _getch();
		if (key_input == '\r' || key_input == 27)
		{
			break;
		}
	}

	clear_console();
	show_console_cursor(false);
}

void message_dialog(string message)
{
	clear_console();
	show_console_cursor(true);

	int content_max_width = 54;
	int content_len = message.length();
	int content_height = (content_len / content_max_width) + (content_len % content_max_width > 0);
	int frame_height = content_height + 4;
	int margin_dialog_y = (25 - frame_height) / 2;

	show_dialog_header(30, 90, margin_dialog_y, "Сообщение");
	show_dialog_content_frame(30, 90, margin_dialog_y + 5, frame_height);

	int content_max_x = 88;
	int current_content_x = 32;
	int current_content_y = margin_dialog_y + 6;

	int wrap_description_count = wrap_dialog_text(current_content_x, content_max_x, current_content_y, message);
	int button_y = current_content_y + wrap_description_count + 2;

	set_console_color(cr::black, cr::light_gray);
	set_position(57, button_y);
	cout << "[Закрыть]";
	set_console_color(cr::light_gray, cr::black);

	while (true)
	{
		int key_input = _getch();
		if (key_input == '\r' || key_input == 27)
		{
			break;
		}
	}

	clear_console();
	show_console_cursor(false);
}