#include <iostream>
#include <iomanip>
#include <string>
#include "components.h"
#include "colors.h"
#include "../helpers/console.h"
#include "../helpers/text.h"
using namespace std;


ConsoleTextInput::ConsoleTextInput(int x, int y, int max_width, string label)
{
	this->set_x(x);
	this->set_y(y);
	this->set_max_width(max_width);
	this->max_input_len = 0;
	this->set_label(label);
	this->error_message = "";
	this->text_input = "";
}

int ConsoleTextInput::get_x()
{
	return this->x;
}
void ConsoleTextInput::set_x(int x)
{
	this->x = x > 0 ? x : 0;
}

int ConsoleTextInput::get_y()
{
	return this->y;
}
void ConsoleTextInput::set_y(int y)
{
	this->y = y > 0 ? y : 0;
}

int ConsoleTextInput::get_max_width()
{
	return this->max_width;
}

void ConsoleTextInput::set_max_width(int max_width)
{
	this->max_width = max_width > 0 ? max_width : 60;
}

string ConsoleTextInput::get_label()
{
	return this->label;
}
void ConsoleTextInput::set_label(string label)
{
	this->label = label;
}

int ConsoleTextInput::get_max_input_len()
{
	return this->max_input_len;
}
void ConsoleTextInput::set_max_input_len(int max_len)
{
	this->max_input_len = max_len > 0 ? max_len : 0;
}

string ConsoleTextInput::get_error_message()
{
	return this->error_message;
}
void ConsoleTextInput::set_error_message(string error_message)
{
	this->error_message = error_message;
}

void ConsoleTextInput::clear_error(int x, int y)
{
	set_position(this->x, y);
	cout << string(this->max_width, ' ');
	set_position(this->x, y + 1);
	cout << string(this->max_width, ' ');
}

void ConsoleTextInput::show_error(int x, int y, string error_message)
{
	set_position(x, y);
	set_console_color(cr::light_red, cr::black);
	cout << string(this->max_width, '-');
	set_position(x, y + 1);
	cout << error_message;
	int space_dif = this->max_width - error_message.length();
	if (space_dif > 0)
	{
		cout << string(space_dif, ' ');
	}
	set_console_color(cr::light_gray, cr::black);
}

string ConsoleTextInput::get_text_input()
{
	return this->text_input;
}

bool ConsoleTextInput::check_input(function<bool(string)> input_checker, int start_input_y)
{
	if (this->max_input_len > 0 && this->text_input.length() > this->max_input_len)
	{
		string error = "Ошибка. Поле содержит больше " + to_string(max_input_len) + " символов!";
		show_error(this->x, start_input_y + 1, error);
		return false;
	}

	this->text_input = trim(this->text_input);

	if (!input_checker(this->text_input) && !this->error_message.empty())
	{
		show_error(this->x, start_input_y + 1, this->error_message);
		return false;
	}

	return true;
}

bool ConsoleTextInput::wait_input(function<bool(string)> input_checker, string exit)
{
	int start_input_y = this->y;
	if (!this->label.empty())
	{
		start_input_y += 1;
		set_position(this->x, this->y);
		set_console_color(cr::fg_active_text, cr::black);
		cout << label;
	}
	set_console_color(cr::light_gray, cr::black);

	bool is_exit = false;
	bool is_completed = false;
	while (!is_exit)
	{
		set_position(this->x, start_input_y);
		cout << string(this->max_width, ' ');
		set_position(this->x, start_input_y);
		getline(cin, this->text_input);

		if (this->text_input == exit)
		{
			is_exit = true;
			continue;
		}

		if (!check_input(input_checker, start_input_y))
		{
			continue;
		}

		is_exit = true;
		is_completed = true;
	}

	if (!this->error_message.empty())
	{
		clear_error(this->x, start_input_y + 1);
	}

	return is_completed;
}