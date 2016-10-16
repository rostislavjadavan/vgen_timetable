#pragma once

#include "cinder/app/App.h"
#include "cinder/Json.h"
using namespace ci;
using namespace ci::app;

#include <vector>
#include <string>
using namespace std;

struct ConfigDj {
	string name;
	string timeFrom, timeTo;
	int fontSize;
	
	int getTimeFrom() {
		vector<string> item = split(timeFrom, ":");
		if (item.size() != 2) {
			return 0;
		}
		return stoi(item[0]) * 3600 + stoi(item[1]) * 60;
	}
	int getTimeTo() {
		vector<string> item = split(timeTo, ":");
		if (item.size() != 2) {
			return 0;
		}
		return stoi(item[0]) * 3600 + stoi(item[1]) * 60;
	}

	bool isLoaded() {
		return name.length() > 0;
	}
};

class TimetableConfig {
public:
	string fontName;
	int fontSize;
	int transitionTime;
	int displayTime, intervalTime;
	vector<ConfigDj> djs;		

	bool load(string filename);
	ConfigDj findDjByTime(int time);
};

