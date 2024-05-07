#pragma once
#include <iostream>
using namespace std;

void show_frame_line(int start_x, int start_y, int length);
void show_dialog_header(int start_x, int end_x, int start_y, string title);
void show_dialog_content_frame(int start_x, int end_x, int start_y, int frame_height);
bool question_dialog(string title, string content);
