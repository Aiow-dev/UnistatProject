#pragma once
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

class ConsoleTextInput
{
private:
	int x;
	int y;
	int max_width;
	string label;
	int max_input_len;
	string error_message;
	string text_input;

	void clear_error(int x, int y);
	void show_error(int x, int y, string error_message);

public:
	ConsoleTextInput(int x, int y, int max_width, string label="");

	int get_x();
	void set_x(int x);

	int get_y();
	void set_y(int y);

	int get_max_width();
	void set_max_width(int max_width);

	string get_label();
	void set_label(string label);

	int get_max_input_len();
	void set_max_input_len(int max_len);

	string get_error_message();
	void set_error_message(string error_message);

	string get_text_input();
	bool check_input(function<bool(string)> input_checker, int start_input_y);

	bool wait_input(function<bool(string)> input_checker, string exit = "");
};

class ConsoleList
{
private:
	int x;
	int y;
	int max_item_width;
	string label;
	int items_size;
	vector<string> items{};

	void set_items_size(int items_size);
	int get_max_item_width();
	void update_max_item_width(int width);
public:
	ConsoleList(int x, int y, vector<string> items, string label = "");

	int get_x();
	void set_x(int x);

	int get_y();
	void set_y(int y);

	string get_label();
	void set_label(string label);

	void add_item(string item);
	void remove_item(int index);

	void show_disable();

	int wait_get_item();
};

class ConsoleWaitButton
{
private:
	int x;
	int y;
	int exit_key;
	int confirm_key;
	string text;
public:
	ConsoleWaitButton(int x, int y, string text);

	int get_x();
	void set_x(int x);

	int get_y();
	void set_y(int y);

	int get_exit_key();
	void set_exit_key(int exit_key);

	int get_confirm_key();
	void set_confirm_key(int confirm_key);

	string get_text();
	void set_text(string text);

	void show_disable();
	void show_enable();

	bool wait();
};