#pragma once
#include <iostream>
using namespace std;

string trim(string text);
string replace_symbol(string text, char from, char to);
int count_symbol(string text, char symbol);
bool is_letters_text(string text);
bool is_digits_text(string text);
bool is_dnumber(string text);
bool is_dnumber_point(string text);
string add_num(string num_text);
