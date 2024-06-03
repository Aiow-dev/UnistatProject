#include <iostream>
#include <conio.h>
#include "../../models/stat_model.h"
#include "../../helpers/console.h"
#include "../../visual/dialogs.h"
#include "../../visual/components.h"
#include "../../visual/colors.h"
using namespace std;

stat_record_filter show_filter_stat_page()
{
	clear_console();
	show_dialog_header(22, 100, 8, "Выберите параметр фильтра");
	show_dialog_content_frame(22, 100, 13, 8);

	string exit_text = "Для выхода нажмите клавишу Enter или Esc после выбора параметра";
	int exit_text_center_x = text_to_dialog_center(22, 100, exit_text.length());
	set_position(exit_text_center_x, 14);
	cout << exit_text;

	string button_text = "[Подтвердить]";
	int button_text_center_x = text_to_dialog_center(22, 100, button_text.length());
	ConsoleWaitButton button(button_text_center_x, 19, button_text);
	button.set_exit_key(72);
	button.show_disable();
	set_console_color(cr::light_gray, cr::black);

	stat_record_filter filter{"id", "min", "", true};

	vector<string> filter_parameters = {"id записи", "Средний балл"};
	ConsoleList key_list(24, 16, filter_parameters, "Параметр фильтра:");

	vector<string> filter_comparison = { "Больше", "Меньше" };
	ConsoleList comparison_list(54, 16, filter_comparison, "Сравнение:");
	comparison_list.show_disable();

	vector<string> filter_value = { "Самое низкое значение", "Среднее", "Самое высокое значение" };
	ConsoleList value_list(77, 16, filter_value, "Параметр сравнения:");
	value_list.show_disable();

	int key_index = key_list.wait_get_item();
	if (key_index == 1)
	{
		filter.filter_parameter = "avg_grade";
	}

	while (true)
	{
		int key = _getch();

		if (key == 27)
		{
			set_console_color(cr::light_gray, cr::black);
			clear_console();
			return stat_record_filter{};
		}

		if (key == 77)
		{
			break;
		}

		if (key == 80)
		{
			bool is_confirm = button.wait();
			if (is_confirm)
			{
				set_console_color(cr::light_gray, cr::black);
				clear_console();
				return filter;
			}
			else
			{
				button.show_disable();
				break;
			}
		}
	}

	key_index = comparison_list.wait_get_item();
	filter.filter_comparison = key_index == 0;

	while (true)
	{
		int key = _getch();

		if (key == 27)
		{
			set_console_color(cr::light_gray, cr::black);
			clear_console();
			return stat_record_filter{};
		}

		if (key == 77)
		{
			break;
		}

		if (key == 80)
		{
			bool is_confirm = button.wait();
			if (is_confirm)
			{
				set_console_color(cr::light_gray, cr::black);
				clear_console();
				return filter;
			}
			else
			{
				button.show_disable();
				break;
			}
		}
	}

	key_index = value_list.wait_get_item();
	string value_parameter = "min";
	switch (key_index)
	{
	case 1: value_parameter = "avg";
		break;
	case 2: value_parameter = "max";
		break;
	}

	filter.filter_value_parameter = value_parameter;

	set_console_color(cr::light_gray, cr::black);
	clear_console();

	return filter;
}