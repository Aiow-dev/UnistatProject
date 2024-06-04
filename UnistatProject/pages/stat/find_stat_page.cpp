#include <iostream>
#include <conio.h>
#include <iomanip>
#include "../../models/stat_model.h"
#include "../../helpers/console.h"
#include "../../helpers/text.h"
#include "../../visual/dialogs.h"
#include "../../visual/colors.h"
using namespace std;

find_params show_find_stat_page()
{
	clear_console();
	show_dialog_header(30, 88, 9, "�������� �������� ������");
	show_dialog_content_frame(30, 88, 14, 7);

	string menu_items[] = {
		"[1] id ������",
		"[2] �������",
		"[3] ���",
		"[4] ��������",
		"[5] ������� ����"
	};

	int max_width = menu_items[4].length();

	set_position(51, 15);
	set_console_color(cr::fg_active_marker, cr::bg_active_marker);
	cout << setw(max_width) << menu_items[0];
	set_console_color(cr::light_gray, cr::black);
	set_position(51, 16);
	cout << menu_items[1];
	set_position(51, 17);
	cout << menu_items[2];
	set_position(51, 18);
	cout << menu_items[3];
	set_position(51, 19);
	cout << menu_items[4];

	int menu_y = 15;
	int menu_pointer = 0;

	while (true)
	{
		int key = _getch();

		set_position(51, menu_y + menu_pointer);
		cout << left << setw(max_width) << menu_items[menu_pointer];

		if (key == 72)
		{
			menu_pointer--;
		}
		if (key == 80)
		{
			menu_pointer++;
		}
		if (key >= 49 && key <= 53)
		{
			int digit = key - '0';
			menu_pointer = digit - 1;
		}
		if (key == '\r')
		{
			break;
		}
		if (key == 27)
		{
			clear_console();

			find_params record_find{ "", "" };
			return record_find;
		}

		if (menu_pointer < 0)
		{
			menu_pointer = 4;
		}
		if (menu_pointer > 4)
		{
			menu_pointer = 0;
		}

		set_position(51, menu_y + menu_pointer);
		set_console_color(cr::fg_active_marker, cr::bg_active_marker);
		cout << left << setw(max_width) << menu_items[menu_pointer];
		set_console_color(cr::light_gray, cr::black);
	}

	string find_parameter = "";
	string find_value = "";

	switch (menu_pointer)
	{
	case 0:
	{
		find_parameter = "id";
		find_value = input_dialog("id ������", is_digits_text, 25, "������. ���� ������ ��������� ������ �����!");
		break;
	}
	case 1:
	{
		find_parameter = "surname";
		find_value = input_dialog("�������", is_letters_text, 25, "������. ���� ������ ��������� ������ �����!");
		break;
	}
	case 2:
	{
		find_parameter = "firstname";
		find_value = input_dialog("���", is_letters_text, 25, "������. ���� ������ ��������� ������ �����!");
		break;
	}
	case 3:
	{
		find_parameter = "patronymic";
		find_value = input_dialog("��������", is_letters_text, 25, "������. ���� ������ ��������� ������ �����!");
		break;
	}
	case 4:
	{
		find_parameter = "avg_grade";
		string input_value = input_dialog("������� ����", is_dnumber_point, 10, "������. ���� ������ ���� ������ �� 1 �� 10!");
		find_value = replace_symbol(input_value, '.', ',');
		break;
	}
	}

	find_params record_find{find_parameter, find_value};
	return record_find;
}