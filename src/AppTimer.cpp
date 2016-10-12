#include "AppTimer.h"

void AppTimer::start()
{
	timer.start();
}

void AppTimer::stop()
{
	timer.stop();
}

double AppTimer::getTime()
{
	return timer.getSeconds();
}

int AppTimer::getGlobalTime()
{
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec;
}

vector<string> AppTimer::getDebug()
{
	vector<string> output;
	char buffer[64];
	string text;
	
	sprintf(buffer, "%.1f", timer.getSeconds());
	text = "apptimer.timer=" + string(buffer) + "s";	
	output.push_back(text);

	text = "apptimer.global_time=" + toString(this->getGlobalTime()) + "s";
	output.push_back(text);

	return output;
}
