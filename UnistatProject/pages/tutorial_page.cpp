#include <iostream>
#include <map>
#include <Windows.h>
#include <conio.h>
#include "../helpers/console.h"
#include "../settings.h"
#include "../visual/colors.h"
#include "../visual/dialogs.h"
using namespace std;
using namespace setting;

void show_tutorial_page()
{
	int field_start_x = 25;
	int field_end_x = 94;
	int frame_height = 16;

	show_dialog_header(field_start_x, field_end_x, 5, "Добро пожаловать в приложение Unistat!");
	show_dialog_content_frame(field_start_x, field_end_x, 10, frame_height);

	int current_x = 31;
	int current_y = 11;
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
		"[Enter] - Подтвердить",
		"[Esc] - Вернуться к предыдущей странице"
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

	current_y += 1;
	set_position(46, current_y);
	set_console_color(cr::fg_active_marker, cr::bg_active_marker);
	cout << "[Enter] Больше не показывать";
	set_console_color(cr::light_gray, cr::black);

	while (true)
	{
		char key = _getch();

		if (key == '\r')
		{
			set_parameter("showTutorial", "false");
			clear_console();

			return;
		}
	}
}