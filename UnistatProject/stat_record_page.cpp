#include <iostream>
#include <conio.h>
#include "stat_model.h"
#include "console.h"
#include "colors.h"
#include "stat.h"
using namespace std;

void show_stat_record_page(stat_record record)
{
	show_console_cursor(true);

	set_position(30, 6);
	cout << "+---------------------------------------------------------+";
	set_position(30, 7);
	cout << "|";
	set_position(88, 7);
	cout << "|";
	set_position(30, 8);
	cout << "|";
	set_position(88, 8);
	cout << "|";
	set_position(51, 8);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "��������� ������";
	set_console_color(cr::light_gray, cr::black);
	set_position(30, 9);
	cout << "|";
	set_position(88, 9);
	cout << "|";
	set_position(30, 10);
	cout << "+---------------------------------------------------------+";

	int field_y = 11;

	for (int i = 0; i < 12; i++)
	{
		set_position(30, field_y);
		cout << "|";
		set_position(88, field_y);
		cout << "|";
		field_y++;
	}

	set_position(30, field_y);
	cout << "+---------------------------------------------------------+";

	set_position(36, 12);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "id: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.id;
	set_position(36, 14);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "�������: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.surname;
	set_position(36, 15);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "���: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.first_name;
	set_position(36, 16);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "��������: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.patronymic;
	set_position(36, 17);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "�������: ";
	set_console_color(cr::light_gray, cr::black);
	cout << record.grades[0] << " " << record.grades[1] << " " << record.grades[2] << " " << record.grades[3];
	set_position(36, 18);
	set_console_color(cr::fg_active_text, cr::black);
	cout << "������� ����: ";
	set_console_color(cr::light_gray, cr::black);
	cout << get_record_grades_avg(record);

	set_position(76, 21);
	set_console_color(cr::black, cr::light_red);
	cout << "�������";
	set_position(45, 21);
	set_console_color(cr::black, cr::light_gray);
	cout << "�������������";
	set_position(36, 21);
	cout << "�����";

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
			break;
		}

		if (current_btn == 0)
		{
			set_position(41, 21);
		}
		if (current_btn == 1)
		{
			set_position(58, 21);
		}
		if (current_btn == 2)
		{
			set_position(83, 21);
		}
	}

	set_console_color(cr::light_gray, cr::black);
	show_console_cursor(false);
}