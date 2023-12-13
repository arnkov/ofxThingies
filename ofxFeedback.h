#pragma once

#include "ofMain.h"

//heavily inspired by https://p5js.org/examples/3d-simple-feedback.html

struct ofxFeedback {
	void setup(float width, float height) {
		this->width = width;
		this->height = height;
		target.allocate(width, height, GL_RGBA32F_ARB);
		buffer.allocate(width, height, GL_RGBA32F_ARB);
	}

	void begin() {
		capture.begin();
	}

	void end() {
		buffer.draw(0, 0, width, height);
		capture.end();
		buffer.begin();
		capture.draw(
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
	ofFbo capture;
	ofFbo buffer; 
};
