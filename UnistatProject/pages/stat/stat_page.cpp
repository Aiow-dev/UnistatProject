#include <iostream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <string>
#include "find_stat_page.h"
#include "../../helpers/console.h"
#include "../../visual/colors.h"
#include "../../visual/dialogs.h"
#include "../../controllers/stat.h"
#include "../../controllers/stat_record.h"
#include "../../app.h"
using namespace std;

void show_table_title(int x, int y, int snm_width, int frt_width, int ptc_width)
{
	set_position(x, y);
	set_console_color(cr::black, cr::bg_active_marker);

	cout << left << setw(snm_width) << "Фамилия" << setw(frt_width) << "Имя"
		<< setw(ptc_width) << "Отчество" << setw(20) << "Отметки" << setw(12);
	cout << "Средний балл" << endl;
	set_console_color(cr::light_gray, cr::black);
	set_position(x, y + 1);
	cout << setfill('-') << setw(snm_width) << "" << setw(frt_width) << ""
		<< setw(ptc_width) << "" << setw(32) << "" << endl;
	cout << setfill(' ');
}

void show_default_node(stat_record record, int x, int y, int snm_width, int frt_width, int ptc_width)
{
	set_position(x, y);
	cout << left << setw(snm_width) << record.surname
		<< setw(frt_width) << record.first_name
		<< setw(ptc_width) << record.patronymic
		<< setw(5) << record.grades[0] << setw(5) << record.grades[1]
		<< setw(5) << record.grades[2] << setw(5) << record.grades[3]
		<< setw(12);
	set_console_color(cr::fg_active_text, cr::black);

	double node_grades_avg = get_record_grades_avg(record);
	cout << node_grades_avg << endl;
	set_console_color(cr::light_gray, cr::black);
}

void show_active_node(stat_record record, int x, int y, int snm_width, int frt_width, int ptc_width)
{
	set_position(x, y);
	set_console_color(cr::fg_active_marker, cr::bg_active_marker);
	cout << left << setw(snm_width) << record.surname
		<< setw(frt_width) << record.first_name
		<< setw(ptc_width) << record.patronymic
		<< setw(5) << record.grades[0] << setw(5) << record.grades[1]
		<< setw(5) << record.grades[2] << setw(5) << record.grades[3]
		<< setw(12);

	double node_grades_avg = get_record_grades_avg(record);
	cout << node_grades_avg << endl;
	set_console_color(cr::light_gray, cr::black);
}

void show_table_footer(int x, int y, double stat_avg, int snm_width, int frt_width, int ptc_width)
{
	set_position(x, y);
	cout << setfill('-') << setw(snm_width) << "" << setw(frt_width) << ""
		<< setw(ptc_width) << "" << setw(32) << "" << endl;
	cout << setfill(' ');

	int table_width = snm_width + frt_width + ptc_width - 8;
	set_position(x, y + 1);
	cout << "Средний балл по университету" << setw(table_width) << "";
	set_console_color(cr::fg_active_text, cr::black);
	cout << stat_avg << endl;
	set_console_color(cr::light_gray, cr::black);
}

void show_table_nodes(vector<stat_record> records, int x, int y, int snm_width, int frt_width, int ptc_width)
{
	if (records.empty())
	{
		return;
	}

	int page_size = 10;
	int size = records.size();

	show_active_node(records[0], x, y, snm_width, frt_width, ptc_width);
	
	for (int i = 1; i < page_size; i++)
	{
		y++;

		if (i < size)
		{
			show_default_node(records[i], x, y, snm_width, frt_width, ptc_width);
		}
		else
		{
			set_position(x, y);
			cout << left << setw(78) << " " << endl;
		}
	}
}

void update_stat_table(vector<stat_record> records, int snm_width, int frt_width, int ptc_width)
{
	int size = records.size();
	int page_size = 10;
	int page_num = size / page_size;
	int offset = size % page_size;

	if (offset != 0)
	{
		page_num++;
	}

	show_table_title(20, 8, snm_width, frt_width, ptc_width);
	vector<stat_record> part_nodes = slice_records(records, 0, 9);
	show_table_nodes(part_nodes, 20, 10, snm_width, frt_width, ptc_width);

	double stat_avg = get_records_grades_avg(records);

	show_table_footer(20, 20, stat_avg, snm_width, frt_width, ptc_width);
	set_position(20, 23);
	cout << "Страница 1" << " из " << page_num;
	set_position(80, 23);
	cout << "Всего записей: " << size;
	show_active_node(records[0], 20, 10, snm_width, frt_width, ptc_width);
}

void update_stat_page()
{
	show_dialog_header(12, 108, 2, "Ведомость абитуриентов (Нажмите + для создания новой записи)");
	show_dialog_content_frame(12, 108, 7, 20);

	set_position(20, 25);
	set_console_color(cr::black, cr::light_gray);
	cout << "<--";
	set_position(34, 25);
	cout << "[S] Сортировать";
	set_position(55, 25);
	cout << "[R] Поиск";
	set_position(70, 25);
	cout << "[F] Фильтровать";
	set_position(95, 25);
	cout << "-->";
	set_console_color(cr::light_gray, cr::black);
}

string run_table_actions(vector<stat_record> records, int x, int y, int snm_width, int frt_width, int ptc_width)
{
	int page_size = 10;
	int start_page_index = 0;
	int end_page_index = 9;
	int current_page_index = 0;

	int size = records.size();
	if (size < page_size)
	{
		end_page_index = size - 1;
	}

	int page_count = size / page_size;
	int page_offset = size % page_size;

	if (page_offset != 0)
	{
		page_count++;
	}

	int current_node_index = 0;

	while (true)
	{
		int key_input = _getch();
		//cout << key_input;

		if (key_input == 72)
		{
			int page_node_index = current_node_index % page_size;

			if (page_node_index == 0)
			{
				continue;
			}

			show_default_node(records[current_node_index], x, y + page_node_index, snm_width, frt_width, ptc_width);
			current_node_index--;
			page_node_index--;
			show_active_node(records[current_node_index], x, y + page_node_index, snm_width, frt_width, ptc_width);
		}

		if (key_input == 80)
		{
			if (current_node_index == size - 1)
			{
				continue;
			}

			int page_node_index = current_node_index % page_size;

			if (page_node_index == page_size - 1)
			{
				continue;
			}

			show_default_node(records[current_node_index], x, y + page_node_index, snm_width, frt_width, ptc_width);
			current_node_index++;
			page_node_index++;
			show_active_node(records[current_node_index], x, y + page_node_index, snm_width, frt_width, ptc_width);
		}

		if (key_input == 75)
		{
			if (start_page_index == 0)
			{
				continue;
			}

			start_page_index -= page_size;
			end_page_index -= page_size;
			current_node_index = start_page_index;
			current_page_index--;

			vector<stat_record> page_nodes = slice_records(records, start_page_index, end_page_index);
			show_table_nodes(page_nodes, x, y, snm_width, frt_width, ptc_width);

			set_position(20, 23);
			cout << "Страница " << current_page_index + 1 << " из " << page_count;
		}

		if (key_input == 77)
		{
			if (end_page_index >= size - 1)
			{
				continue;
			}

			start_page_index += page_size;
			end_page_index += page_size;
			current_node_index = start_page_index;
			current_page_index++;

			vector<stat_record> page_nodes = slice_records(records, start_page_index, end_page_index);
			show_table_nodes(page_nodes, x, y, snm_width, frt_width, ptc_width);

			set_position(20, 23);
			cout << "Страница " << current_page_index + 1 << " из " << page_count;
		}

		if (key_input == 43)
		{
			clear_console();
			return app_action::create_stats_record_page;
		}

		if (key_input == 114)
		{
			stat_record_find find_parameters = show_find_stat_page();
			if (find_parameters.find_parameter.empty() || find_parameters.find_value.empty())
			{
				update_stat_page();
				update_stat_table(records, snm_width, frt_width, ptc_width);
				continue;
			}
			records = find_records(records, find_parameters);

			if (records.empty())
			{
				message_dialog("Нет найденных записей!");
				return app_action::stats_page;
			}

			size = records.size();
			if (size < page_size)
			{
				end_page_index = size - 1;
			}

			page_count = size / page_size;
			page_offset = size % page_size;

			if (page_offset != 0)
			{
				page_count++;
			}
			update_stat_page();
			update_stat_table(records, snm_width, frt_width, ptc_width);
		}

		if (key_input == '\r')
		{
			stat_record_controller::set_active_record(records[current_node_index]);
			return app_action::stats_record_page;
		}
		if (key_input == 27)
		{
			clear_console();
			return app_action::start_page;
		}
	}
}

string show_table()
{
	try
	{
		vector<stat_record> records = read_student_stat(fm::get_fmodel());

		if (records.empty())
		{
			message_dialog("Нет записей в ведомости абитуриентов!");
			return app_action::start_page;
		}

		int snm_width = 0;
		int frt_width = 0;
		int ptc_width = 0;

		for (stat_record student : records)
		{
			int st_surname_len = student.surname.length();
			int st_first_name_len = student.first_name.length();
			int st_patronymic_len = student.patronymic.length();

			if (snm_width < st_surname_len)
			{
				snm_width = st_surname_len;
			}
			if (frt_width < st_first_name_len)
			{
				frt_width = st_first_name_len;
			}
			if (ptc_width < st_patronymic_len)
			{
				ptc_width = st_patronymic_len;
			}
		}

		snm_width += 5;
		frt_width += 5;
		ptc_width += 5;

		update_stat_table(records, snm_width, frt_width, ptc_width);

		return run_table_actions(records, 20, 10, snm_width, frt_width, ptc_width);
	}
	catch (exception e)
	{
		error_dialog(e.what());
		return app_action::exit_app;
	}
}

string show_stat_page()
{
	update_stat_page();
	return show_table();
}