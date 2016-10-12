#pragma once

#include "cinder/gl/gl.h"
using namespace ci;
using namespace std;

class Console {
public:
	void add(string line) {
		lines.push_back(line);
	}

	void add(vector<string> lines) {
		for (string line : lines) {
			this->lines.push_back(line);
		}
	}

	gl::TextureRef getOutput() {
		string output;
		for (string line : lines) {
			output += line + "\n";
		}
		lines.clear();
		return gl::Texture2d::create(
			TextBox()
			.alignment(TextBox::LEFT)
			.font(Font("Verdana", 14))
			.color(ColorA(1, 1, 1, 1))
			.text(output)
			.render()
		);
	}
private:
	vector<string> lines;
};