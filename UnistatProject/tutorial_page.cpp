#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "console.h"
#include "start.h"
using namespace std;

void show_tutorial_page()
{
	int field_start_x = 25;
	int field_end_x = 94;

	set_position(field_start_x, 5);
	cout << "+--------------------------------------------------------------------+";
	set_position(42, 7);
	set_console_color(3, 0);
	cout << "Добро пожаловать в приложение Unistat!";
	set_console_color(7, 0);

	int field_y = 6;
	for (int i = 0; i < 18; i++)
	{
		set_position(field_start_x, field_y);
		cout << "|";
		set_position(field_end_x, field_y);
		cout << "|";
		field_y++;
	}
	set_position(field_start_x, field_y);
	cout << "+--------------------------------------------------------------------+";

	int current_x = 31;
	int current_y = 9;
	set_position(current_x, current_y);

	int end_text_x = field_end_x - 6;
	string text = "С помощью этого небольшого приложения можно быстро и эффективно обрабатывать результаты сдачи "
		"абитуриентами вступительных экзаменов в университет. Для навигации в приложении используйте клавиши клавиатуры:";

	for (int i = 0; i < text.length(); i++)
	{
		if (current_x > end_text_x)
		{
			current_x = 31;
			current_y++;
			set_position(current_x, current_y);
		}
		cout << text[i];
		current_x++;
		Sleep(30);
	}

	current_x = 31;
	current_y += 2;
	set_position(current_x, current_y);
	string keyboard_items[] = {
		"[^] (стрелка вверх) - Переместиться вверх",
		"[<] (стрелка влево) - Переместиться влево",
		"[>] (стрелка вправо) - Переместиться вправо",
		"[v] (стрелка вниз) - Переместиться вниз",
		"[1-9] (клавиши цифр) - Выбрать пункт меню",
		"[Enter] - Подтвердить"
	};

	for (string keyboard_item : keyboard_items)
	{
		set_position(current_x, current_y);
		for (int i = 0; i < keyboard_item.length(); i++)
		{
			cout << keyboard_item[i];
			Sleep(30);
		}
		current_y++;
	}

	current_y += 2;
	set_position(46, current_y);
	set_console_color(0, 3);
	cout << "[Enter] Больше не показывать";
	set_console_color(7, 0);

	char key = _getch();
	if (key == '\r')
	{
		clear_console();
		return;
	}
}