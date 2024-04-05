#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include "colors.h"
using namespace std;

void set_console_color(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bg_color << 4) | fg_color));
}

void set_position(int x, int y)
{
	COORD c{};
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clear_console()
{
	system("cls");
}

void show_console_cursor(bool show_flag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(out, &cursor_info);
	cursor_info.bVisible = show_flag;
	SetConsoleCursorInfo(out, &cursor_info);
}

int get_console_columns()
{
	CONSOLE_SCREEN_BUFFER_INFO screen_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_info);
	return screen_info.srWindow.Right - screen_info.srWindow.Left + 1;
}

int get_console_rows()
{
	CONSOLE_SCREEN_BUFFER_INFO screen_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_info);
	return screen_info.srWindow.Bottom - screen_info.srWindow.Top + 1;
}

int menu(int points_num, string* points, int start_x, int start_y, int point_width)
{
	int max_index = points_num - 1;
	int x = start_x;
	int y = start_y;
	int counter = 0;
	char key;

	while (true)
	{
		y = start_y;

		for (int i = 0; i < points_num; i++)
		{
			set_position(x, y);
			if (counter == i)
			{
				set_console_color(cr::fg_active_marker, cr::bg_active_marker);
			}
			else
			{
				set_console_color(7, 0);
			}
			cout << left << setw(point_width) << points[i];
			y++;
		}

		key = _getch();

		if (key == 72)
		{
			counter--;
		}
		if (key == 80)
		{
			counter++;
		}
		if (key >= 49 && key <= 57)
		{
			int digit = key - '0';
			if (digit <= points_num)
			{
				counter = digit - 1;
			}
		}
		if (key == '\r')
		{
			set_console_color(7, 0);
			return counter;
		}

		if (counter < 0) {
			counter = max_index;
		}
		if (counter > max_index) {
			counter = 0;
		}
	}
}