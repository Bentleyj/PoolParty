#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ImageAnalyzer: public ofThread {
public:
	ImageAnalyzer();

	void setup(int _width, int _height) {
		//largeImg.create()
		largeImg.allocate(_width, _height, OF_IMAGE_COLOR);
		//smallImg.allocate(largeImg.cols() * scale, largeImg.getHeight() * scale, OF_IMAGE_COLOR);
		//smallGray.allocate(largeImg.getWidth() * scale, largeImg.getHeight() * scale, OF_IMAGE_GRAYSCALE);
		width = _width;
		height = _height;
	}

	void threadedFunction() {

	}


	ofImage largeImg;
	cv::Mat smallImg;
	cv::Mat smallGray;

	float scale = 0.1;
	float width;
	float height;


private:


};