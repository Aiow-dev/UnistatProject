#pragma once
#include <iostream>
#include <functional>
using namespace std;

int text_to_dialog_center(int start_x, int end_x, int text_len);
void show_frame_line(int start_x, int start_y, int length);
void show_dialog_header(int start_x, int end_x, int start_y, string title);
void show_error_dialog_header(int start_x, int end_x, int start_y);
void show_dialog_content_frame(int start_x, int end_x, int start_y, int frame_height);
int wrap_dialog_text(int start_x, int end_x, int start_y, string text);
bool question_dialog(string title, string content);
void error_dialog(string error);
void message_dialog(string message);
string input_dialog(string parameter, function<bool(string)> input_checker, int input_len, string error);
