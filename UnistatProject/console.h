#pragma once
#include <iostream>
using namespace std;

void set_color(int color);
void set_position(int x, int y);
void clear_console();
int menu(int points_num, string* points, int start_x = 1, int start_y = 3);
