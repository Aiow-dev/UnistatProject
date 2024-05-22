#pragma once
#include <iostream>
using namespace std;

void show_frame_line(int start_x, int start_y, int length);
void show_dialog_header(int start_x, int end_x, int start_y, string title);
void show_error_dialog_header(int start_x, int end_x, int start_y);
void show_dialog_content_frame(int start_x, int end_x, int start_y, int frame_height);
int wrap_dialog_text(int start_x, int end_x, int start_y, string text);
bool question_dialog(string title, string content);
void error_dialog(string error);
void message_dialog(string message);
