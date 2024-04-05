#include <iostream>
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