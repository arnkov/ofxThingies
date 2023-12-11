#pragma once
#include "ofMain.h"

struct ofxCpuNoise {
	void setup(int w, int h) {
		img.allocate(w, h, OF_IMAGE_GRAYSCALE);
		width = w;
		height = h;
	}
	
	void update() {
		velocity = ofGetElapsedTimef()*0.5f;
		ofPixels& pix = img.getPixels();
		for(int y=0; y<height; y++) {
			for(int  x=0; x<width; x++) {
				int i = y*width+x;
				float nv = ofNoise(x*scale, y*scale, velocity);
				
				pix[i] = 255 * nv;
			}
		}
		img.update();
	}

	void draw(int x, int y, int w, int h){
		img.draw(x, y, w, h);
	}
	//void cleanup();

	ofImage img;
	int width = 0, height = 0;
	float scale = 0.0f;
	float velocity = 0.0f;
};

