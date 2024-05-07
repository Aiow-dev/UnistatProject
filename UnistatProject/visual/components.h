#pragma once
#include <iostream>
#include <functional>
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