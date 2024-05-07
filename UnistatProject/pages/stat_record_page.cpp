#include <iostream>
#include <conio.h>
#include <string>
#include "../models/stat_model.h"
#include "../helpers/console.h"
#include "../helpers/text.h"
#include "../visual/colors.h"
#include "../visual/dialogs.h"
#include "../visual/components.h"
#include "../controllers/stat.h"
#include "../app.h"
using namespace std;

string show_create_stat_record_page()
{
	clear_console();
	show_console_cursor(true);

	show_dialog_header(13, 105, 2, "Создание новой записи");
	show_dialog_content_frame(13, 105, 7, 20);

	set_position(28, 8);
	cout << "Для отмены создания записи нажмите Enter в любом текстовом поле";

	ConsoleTextInput console_input(15, 11, 69, "Фамилия:");
	console_input.set_max_width(43);
	console_input.set_max_input_len(25);
	console_input.set_error_message("Ошибка. Поле должно содержать только буквы!");
	if (!console_input.wait_input(is_letters_text))
	{
		clear_console();
		show_console_cursor(false);
		return app_action::stats_page;
	}
	string surname = console_input.get_text_input();

	console_input.set_x(60);
	console_input.set_label("Имя:");
	if (!console_input.wait_input(is_letters_text))
	{
		clear_console();
		show_console_cursor(false);
		return app_action::stats_page;
	}
	string first_name = console_input.get_text_input();

	console_input.set_x(15);
	console_input.set_y(14);
	console_input.set_label("Отчество:");
	if (!console_input.wait_input(is_letters_text))
	{
		clear_console();
		show_console_cursor(false);
		return app_action::stats_page;
	}
	string patronymic = console_input.get_text_input();

	console_input.set_y(17);
	console_input.set_label("Оценка по первому предмету:");
	console_input.set_max_input_len(10);
	console_input.set_error_message("Ошибка. Поле должно быть числом от 1 до 10!");
	if (!console_input.wait_input(is_dnumber))
	{
		clear_console();
		show_console_cursor(false);
		return app_action::stats_page;
	}
	int sub_grade1 = stoi(console_input.get_text_input());

	console_input.set_x(60);
	console_input.set_label("Оценка по второму предмету:");
	if (!console_input.wait_input(is_dnumber))
	{
		clear_console();
		show_console_cursor(false);
		return app_action::stats_page;
	}
	int sub_grade2 = stoi(console_input.get_text_input());

	console_input.set_x(15);
	console_input.set_y(20);
	console_input.set_label("Оценка по третьему предмету:");
	if (!console_input.wait_input(is_dnumber))
	{
		clear_console();
		show_console_cursor(false);
		return app_action::stats_page;
	}
	int sub_grade3 = stoi(console_input.get_text_input());

	console_input.set_x(60);
	console_input.set_label("Оценка по четвертому предмету:");
	if (!console_input.wait_input(is_dnumber))
	{
		clear_console();
		show_console_cursor(false);
		return app_action::stats_page;
	}
	int sub_grade4 = stoi(console_input.get_text_input());

	stat_record record = {"", surname, first_name, patronymic, {sub_grade1, sub_grade2, sub_grade3, sub_grade4}};

	set_position(40, 23);
	cout << "Подтверждение создания новой записи...";

	set_console_color(cr::black, cr::light_gray);
	set_position(67, 25);
	cout << "[Отмена]";
	set_console_color(cr::black, cr::bg_active_marker);
	set_position(42, 25);
	cout << "[Создать]";
	set_console_color(cr::light_gray, cr::black);

	int current_btn = 0;

	while (true)
	{
		int key_input = _getch();

		if (key_input == 75 && current_btn > 0)
		{
			set_position(51, 25);
			current_btn--;
		}
		if (key_input == 77 && current_btn < 2)
		{
			set_position(75, 25);
			current_btn++;
		}
		if (key_input == 27)
		{
			break;
		}
		if (key_input == '\r')
		{
			if (current_btn == 0)
			{
				try
				{
					create_frecord(fm::get_fmodel(), fm::get_index_model(), record);
				}
				catch (exception e)
				{
					break;
				}
			}
			break;
		}
	}

	clear_console();
	show_console_cursor(false);

	return app_action::stats_page;
}

string show_stat_record_page(stat_record record)
{
	clear_console();
	show_console_cursor(true);

	show_dialog_header(30, 88, 6, "Выбранная запись");
	show_dialog_content_frame(30, 88, 11, 12);

	set_position(36, 12);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "id: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.id;
	set_position(36, 14);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "Фамилия: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.surname;
	set_position(36, 15);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "Имя: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.first_name;
	set_position(36, 16);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "Отчество: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.patronymic;
	set_position(36, 17);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "Отметки: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.grades[0] << " " << record.grades[1] << " " << record.grades[2] << " " << record.grades[3];
	set_position(36, 18);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "Средний балл: ";
	set_console_color(cr::light_gray, cr::black);
	cout << get_record_grades_avg(record);

	set_position(74, 21);
	set_console_color(cr::black, cr::light_red);
	cout << "[Удалить]";
	set_position(48, 21);
	set_console_color(cr::black, cr::light_gray);
	cout << "[Редактировать]";
	set_position(36, 21);
	cout << "[Выйти]";
	set_console_color(cr::light_gray, cr::black);

	int current_btn = 0;

	while (true)
	{
		int key_input = _getch();

		if (key_input == 75 && current_btn > 0)
		{
			current_btn--;
		}
		if (key_input == 77 && current_btn < 2)
		{
			current_btn++;
		}
		if (key_input == '\r')
		{
			if (current_btn == 0)
			{
				break;
			}
			if (current_btn == 2)
			{
				string dialog_content = "Вы уверены, что хотите удалить выбранную запись? После удаления данную запись невозможно будет восстановить!";
				bool is_confirm = question_dialog("Подтвердите действие", dialog_content);
				if (is_confirm)
				{
					delete_frecord_id(fm::get_fmodel(), record.id);
					break;
				}
				return app_action::stats_record_page;
			}
		}
		if (key_input == 27)
		{
			break;
		}

		if (current_btn == 0)
		{
			set_position(43, 21);
		}
		if (current_btn == 1)
		{
			set_position(63, 21);
		}
		if (current_btn == 2)
		{
			set_position(83, 21);
		}
	}

	clear_console();
	show_console_cursor(false);

	return app_action::stats_page;
}