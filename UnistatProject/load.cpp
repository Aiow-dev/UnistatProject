#include <iostream>
#include <windows.h>
#include <conio.h>
#include "console.h"
#include "colors.h"
using namespace std;

void show_loading()
{
	set_position(52, 13);
	cout << "Готовимся к запуску...";
	cout << endl;
	int start_x = 35;
	int y = 15;
	int count_x = 88;
	set_console_color(cr::fg_active_text, cr::black);
	set_position(start_x, y);
	cout << "[";
	set_position(86, y);
	cout << "]";
	int i;

	for (i = 0; i < 49; i++)
	{
		set_position(start_x + i + 1, y);
		cout << "->";
		set_position(count_x, y);
		cout << i * 2 << " %";
		Sleep(20);
	}

	set_position(count_x, y);
	cout << "100 %";
	set_console_color(cr::light_gray, cr::black);
}