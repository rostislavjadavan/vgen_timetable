#pragma once

#include <ctime>
#include "cinder/Utilities.h"
#include "cinder/Timer.h"
using namespace ci;
using namespace std;

class AppTimer {
public:
	void start();
	void stop();
	double getTime();
	int getGlobalTime();
	vector<string> getDebug();
private:
	Timer timer;
};