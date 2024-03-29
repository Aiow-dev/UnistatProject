#include <iostream>
#include "console.h"
#include "load.h"
#include "start.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RuS");

	show_console_cursor(false);
	show_loading();
	clear_console();
	show_start_menu();

	return 0;
}
