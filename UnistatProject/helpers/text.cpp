#include <iostream>
#include <string>
using namespace std;

string trim(string text)
{
	int start = 0;
	while (start < text.length() && isspace(text[start]))
	{
		start++;
	}
	text.erase(0, start);

	int end = text.length() - 1;
	for (; end > 0; end--)
	{
		if (!isspace(text[end]))
		{
			break;
		}
	}
	text.erase(end + 1);

	return text;
}

bool is_letters_text(string text)
{
	int counts = 0;
	string letters = "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";
	for (int i = 0; i < text.length(); i++)
	{
		if (letters.find(tolower(text[i])) != -1)
		{
			counts += 1;
		}
	}

	return counts == text.length();
}

bool is_dnumber(string text)
{
	int text_len = text.length();

	if (text_len == 1)
	{
		return isdigit(text[0]);
	}
	if (text_len == 2)
	{
		return text == "10";
	}

	return false;
}

string add_num(string num_text)
{
	int num_len = num_text.length();
	if (num_len == 0)
	{
		return "";
	}

	int last_digit = num_text[num_len - 1] - '0';
	if (!isdigit(num_text[num_len - 1]))
	{
		return "";
	}
	if (last_digit < 9)
	{
		num_text[num_len - 1] = last_digit + 1 + '0';
		return num_text;
	}

	num_text[num_len - 1] = '0';
	bool is_offset = true;

	for (int i = num_len - 1; i > 0; i--)
	{
		int index = i - 1;

		if (!isdigit(num_text[index]))
		{
			return "";
		}

		int digit = num_text[index] - '0';
		if (digit == 9)
		{
			num_text[index] = '0';
			is_offset = true;
		}
		else if (is_offset)
		{
			num_text[index] = digit + 1 + '0';
			is_offset = false;
			break;
		}
	}

	if (is_offset)
	{
		return "1" + num_text;
	}

	return num_text;
}