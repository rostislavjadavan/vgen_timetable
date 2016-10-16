#include "TextRender.h"

void TextRender::initTimetable(TimetableConfig &config)
{
	this->config = config;
	this->animationState = TRS_INIT;
	this->font = Font(loadAsset(config.fontName), (int)config.fontSize);
}

gl::TextureRef TextRender::render(double t, int globalTime)
{
	TextLayout layout;
	layout.clear(ColorA(0.0f, 0.0f, 0.0f, 0.0f));	
	layout.setFont(font);
	
	double delta;
	switch (this->animationState)
	{		
		case TRS_TEXT_IN:
			delta = t - this->startTime;
			if (this->currentDj.isLoaded()) {
				layout.setColor(ColorA(1.0f, 1.0f, 1.0f, (float)delta / (float)this->config.transitionTime));
				layout.addCenteredLine(currentDj.name);
			}			
			if (delta > this->config.transitionTime) {
				this->startTime = t;
				this->animationState = TRS_TEXT;
			}
			break;
		case TRS_TEXT:
			if (this->currentDj.isLoaded()) {
				layout.setColor(ColorA(1.0f, 1.0f, 1.0f, 1.0f));
				layout.addCenteredLine(currentDj.name);
			}
			delta = t - this->startTime;
			if (delta > this->config.displayTime) {
				this->startTime = t;
				this->animationState = TRS_TEXT_OUT;
			}
			break;
		case TRS_TEXT_OUT:
			delta = t - this->startTime;
			if (this->currentDj.isLoaded()) {
				layout.setColor(ColorA(1.0f, 1.0f, 1.0f, 1.0f - (float)delta / (float)this->config.transitionTime));
				layout.addCenteredLine(currentDj.name);
			}
			if (delta > this->config.transitionTime) {
				this->startTime = t;
				this->animationState = TRS_BLANK;
			}
			break;
		case TRS_BLANK: 
			delta = t - this->startTime;
			if (delta > this->config.intervalTime) {
				this->startTime = t;
				this->animationState = TRS_TEXT_IN;
				this->currentDj = this->config.findDjByTime(globalTime);
			}
			break;		
		default:
		case TRS_INIT:
			this->currentDj = this->config.findDjByTime(globalTime);
			this->animationState = TRS_TEXT_IN;
			this->startTime = t;
			break;
	}	

	Surface8u rendered = layout.render();
	return gl::Texture2d::create(rendered);
}

vector<string> TextRender::getDebug()
{
	vector<string> out;
	if (this->currentDj.isLoaded()) {
		out.push_back("textrender.current_dj=" + currentDj.name);
	}
	for (ConfigDj dj : config.djs) {
		out.push_back("textrender.config.dj=" + dj.name + ", from:" + toString(dj.getTimeFrom()) + ", to: " + toString(dj.getTimeTo()));
	}
	return out;
}
