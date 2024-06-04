#include <iostream>
#include <conio.h>
#include "../../models/stat_model.h"
#include "../../helpers/console.h"
#include "../../visual/dialogs.h"
#include "../../visual/components.h"
#include "../../visual/colors.h"
using namespace std;

sort_params show_sort_stat_page()
{
	clear_console();
	show_dialog_header(22, 100, 8, "Выберите параметры сортировки");
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

	sort_params sort{ "bubble", "id", true };

	vector<string> sort_functions = { "Сортировка пузырьком", "Быстрая сортировка" };
	ConsoleList func_list(24, 16, sort_functions, "Метод сортировки:");

	vector<string> sort_parameters = { "id записи", "Фамилия", "Имя", "Отчество", "Средний балл" };
	ConsoleList parameter_list(52, 16, sort_parameters, "Параметр сортировки:");
	parameter_list.show_disable();

	vector<string> sort_orders = { "По возрастанию", "По убыванию" };
	ConsoleList order_list(80, 16, sort_orders, "Последовательность:");
	order_list.show_disable();

	int key_index = func_list.wait_get_item();
	if (key_index == 1)
	{
		sort.function = "quick";
	}

	while (true)
	{
		int key = _getch();

		if (key == 27)
		{
			set_console_color(cr::light_gray, cr::black);
			clear_console();
			return sort_params{};
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
				return sort;
			}
			else
			{
				button.show_disable();
				break;
			}
		}
	}

	key_index = parameter_list.wait_get_item();
	switch (key_index)
	{
	case 1: sort.parameter = "surname";
		break;
	case 2: sort.parameter = "firstname";
		break;
	case 3: sort.parameter = "patronymic";
		break;
	case 4: sort.parameter = "avg_grade";
		break;
	}

	while (true)
	{
		int key = _getch();

		if (key == 27)
		{
			set_console_color(cr::light_gray, cr::black);
			clear_console();
			return sort_params{};
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
				return sort;
			}
			else
			{
				button.show_disable();
				break;
			}
		}
	}

	key_index = order_list.wait_get_item();
	sort.order = key_index == 0;

	set_console_color(cr::light_gray, cr::black);
	clear_console();

	return sort;
}