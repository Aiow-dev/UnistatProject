#include <iostream>
#include <conio.h>
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
		this->show_error(this->x, start_input_y + 1, error);
		return false;
	}

	this->text_input = trim(this->text_input);

	if (!input_checker(this->text_input) && !this->error_message.empty())
	{
		this->show_error(this->x, start_input_y + 1, this->error_message);
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

		if (!this->check_input(input_checker, start_input_y))
		{
			continue;
		}

		is_exit = true;
		is_completed = true;
	}

	if (!this->error_message.empty())
	{
		this->clear_error(this->x, start_input_y + 1);
	}

	return is_completed;
}

ConsoleList::ConsoleList(int x, int y, vector<string> items, string label)
{
	this->set_x(x);
	this->set_y(y);
	this->set_label(label);
	this->max_item_width = label.length();
	this->items = items;
	this->set_items_size(items.size());
}

int ConsoleList::get_x()
{
	return this->x;
}

void ConsoleList::set_x(int x)
{
	this->x = x > 0 ? x : 0;
}

int ConsoleList::get_y()
{
	return this->y;
}

void ConsoleList::set_y(int y)
{
	this->y = y > 0 ? y : 0;
}

string ConsoleList::get_label()
{
	return this->label;
}

void ConsoleList::set_label(string label)
{
	this->label = label;
}

void ConsoleList::set_items_size(int items_size)
{
	this->items_size = items_size > 0 ? items_size : 0;
}

int ConsoleList::get_max_item_width()
{
	if (this->items_size == 0)
	{
		return this->max_item_width;
	}

	int max_len = this->items[0].length();
	for (int i = 1; i < items_size; i++)
	{
		int item_len = this->items[i].length();
		if (item_len > max_len)
		{
			max_len = item_len;
		}
	}

	if (max_len > this->max_item_width)
	{
		return max_len;
	}
	else {
		return this->max_item_width;
	}
}

void ConsoleList::update_max_item_width(int width)
{
	if (width > this->max_item_width)
	{
		this->max_item_width = width;
	}
}

void ConsoleList::add_item(string item)
{
	this->items.push_back(item);
	this->items_size++;
	this->update_max_item_width(item.length());
}

void ConsoleList::remove_item(int index)
{
	if (index >= 0 && index < this->items_size)
	{
		this->items.erase(this->items.begin() + index);
		this->items_size--;
		this->max_item_width = this->get_max_item_width();
	}
}

void ConsoleList::show_disable()
{
	int start_input_y = this->y;
	if (!this->label.empty())
	{
		start_input_y += 1;
		set_position(this->x, this->y);
		cout << label;
	}

	if (this->items_size == 0)
	{
		return;
	}

	int max_width = 0;

	if (this->items_size == 1)
	{
		max_width = this->items[0].length();
	}
	else
	{
		max_width = this->get_max_item_width();
	}

	set_position(this->x, start_input_y);
	set_console_color(cr::black, cr::light_gray);
	cout << setw(max_width) << this->items[0];
	set_console_color(cr::light_gray, cr::black);
}

int ConsoleList::wait_get_item()
{
	if (this->items_size < 1)
	{
		return -1;
	}

	int max_width = 0;
	if (this->items_size == 1)
	{
		max_width = this->items[0].length();
	}
	else
	{
		max_width = this->get_max_item_width();
	}

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
	int item_pointer = 0;

	while (!is_exit)
	{
		set_position(this->x, start_input_y);
		set_console_color(cr::fg_active_marker, cr::bg_active_marker);
		cout << setw(max_width) << this->items[item_pointer];

		int key = _getch();

		if (key == '\r')
		{
			is_exit = true;
			continue;
		}

		if (key == 72)
		{
			item_pointer--;
		}
		if (key == 80)
		{
			item_pointer++;
		}

		if (item_pointer < 0)
		{
			item_pointer = items_size - 1;
		}
		if (item_pointer > items_size - 1)
		{
			item_pointer = 0;
		}
	}

	return item_pointer;
}

ConsoleWaitButton::ConsoleWaitButton(int x, int y, string text)
{
	this->set_x(x);
	this->set_y(y);
	this->exit_key = 27;
	this->confirm_key = '\r';
	this->set_text(text);
}

int ConsoleWaitButton::get_x()
{
	return this->x;
}

void ConsoleWaitButton::set_x(int x)
{
	this->x = x > 0 ? x : 0;
}

int ConsoleWaitButton::get_y()
{
	return this->y;
}

void ConsoleWaitButton::set_y(int y)
{
	this->y = y > 0 ? y : 0;
}

int ConsoleWaitButton::get_exit_key()
{
	return this->exit_key;
}

void ConsoleWaitButton::set_exit_key(int exit_key)
{
	this->exit_key = exit_key;
}

int ConsoleWaitButton::get_confirm_key()
{
	return this->confirm_key;
}

void ConsoleWaitButton::set_confirm_key(int confirm_key)
{
	this->confirm_key = confirm_key;
}

string ConsoleWaitButton::get_text()
{
	return this->text;
}

void ConsoleWaitButton::set_text(string text)
{
	this->text = text;
}

void ConsoleWaitButton::show_disable()
{
	set_position(this->x, this->y);
	set_console_color(cr::black, cr::light_gray);
	cout << this->text;
}

void ConsoleWaitButton::show_enable()
{
	set_position(this->x, this->y);
	set_console_color(cr::fg_active_marker, cr::bg_active_marker);
	cout << this->text;
}

bool ConsoleWaitButton::wait()
{
	this->show_enable();

	bool is_confirm = false;
	bool is_exit = false;

	while (!is_exit)
	{
		int key = _getch();

		if (key == this->exit_key)
		{
			is_exit = true;
			continue;
		}

		if (key == this->confirm_key)
		{
			is_confirm = true;
			is_exit = true;
			continue;
		}
	}

	return is_confirm;
}