#pragma once
#include <iostream>
using namespace std;

void set_console_color(int foreground_color, int background_color);
void set_position(int x, int y);
void clear_console();
void show_console_cursor(bool show_flag);
int get_console_columns();
int get_console_rows();
int menu(int points_num, string* points, int start_x, int start_y, int point_width);
