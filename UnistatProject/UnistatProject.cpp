#include <iostream>
#include "console.h"
#include "start.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RuS");

	show_console_cursor(false);
	show_start_menu();

	return 0;
}
