#pragma once

#include "TimetableConfig.h"
#include "cinder/Utilities.h"
#include "cinder/Text.h"
#include "cinder/Font.h"
#include "cinder/gl/gl.h"
using namespace std;
using namespace ci;

enum TextRenderStates {
	TRS_INIT, TRS_TEXT_IN, TRS_TEXT_OUT, TRS_TEXT, TRS_BLANK
};

class TextRender {
public:
	void initTimetable(TimetableConfig &config);
	gl::TextureRef render(double t, int globalTime);
	vector<string> getDebug();
private:
	TimetableConfig config;
	Font font;	
	TextRenderStates animationState;
	double startTime;
	ConfigDj currentDj;
};