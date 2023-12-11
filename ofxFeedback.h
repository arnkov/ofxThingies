#pragma once

#include "ofMain.h"

struct ofxFeedback {
	void setup(float width, float height) {
		this->width = width;
		this->height = height;
		target.allocate(width, height, GL_RGBA32F_ARB);
		buffer.allocate(width, height, GL_RGBA32F_ARB);
	}

	void begin() {
		target.begin();
	}

	void end() {
		buffer.draw(0, 0, width, height);
		target.end();
		buffer.begin();
		target.draw(
			-width / scale,
			-height / scale,
			width + (width / (scale * 0.5)),
			height + (height / (scale * 0.5)));
		ofSetColor(0, 0, 0, clearValue);
		ofDrawRectangle(0, 0, width, height);
		buffer.end();
	}

	void draw(float x, float y) {
		buffer.draw(x, y);
	}

	float width, height;
	float scale = 0.f;
	int clearValue = 1;
	ofFbo target;
	ofFbo buffer;
};
