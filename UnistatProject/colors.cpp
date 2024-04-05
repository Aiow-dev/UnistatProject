#include <iostream>
#include <string>
#include "settings.h"
using namespace std;
using namespace setting;


namespace cr
{
	int black = 0;
	int blue = 1;
	int green = 2;
	int cyan = 3;
	int red = 4;
	int magenta = 5;
	int brown = 6;
	int light_gray = 7;
	int dark_gray = 8;
	int light_blue = 9;
	int light_green = 10;
	int light_cyan = 11;
	int light_red = 12;
	int light_magenta = 13;
	int yellow = 14;
	int white = 15;

	int fg_active_text = 14;
	int fg_active_marker = 0;
	int bg_active_marker = 14;

	void read_active_colors()
	{
		string fg_act_text = get_parameter("fgActiveTextColor");
		if (!fg_act_text.empty())
		{
			fg_active_text = stoi(fg_act_text);
		}
		
		string fg_act_marker = get_parameter("fgActiveMarkerColor");
		if (!fg_act_marker.empty())
		{
			fg_active_marker = stoi(fg_act_marker);
		}

		string bg_act_marker = get_parameter("bgActiveMarkerColor");
		if (!bg_act_marker.empty())
		{
			bg_active_marker = stoi(bg_act_marker);
		}
	}
}