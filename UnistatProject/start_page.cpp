#include <iostream>
#include "console.h"
using namespace std;

void show_start_page()
{
	set_position(30, 10);
	cout << "+---------------------------------------------------------+";
	set_position(30, 11);
	cout << "|";
	set_position(88, 11);
	cout << "|";
	set_position(30, 12);
	cout << "|";
	set_position(88, 12);
	cout << "|";
	set_position(51, 12);
	cout << "Выберите действие";
	set_position(30, 13);
	cout << "|";
	set_position(88, 13);
	cout << "|";
	set_position(30, 14);
	cout << "+---------------------------------------------------------+";

	string menu_items[] = {
		"[1] Ведомость абитуриентов"
	};
}