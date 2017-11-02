#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ImageAnalyzer: public ofThread {
public:
	ImageAnalyzer();

	void setup(ofVideoGrabber* _grabber) {
		//largeImg.allocate(_width, _height, OF_IMAGE_COLOR);
		width = _grabber->getWidth();
		height = _grabber->getHeight();
		grabber = _grabber;
	}

	void copyImage() {
		ofxCv::copy(*grabber, largeImg);
		ofxCv::resize(largeImg, smallImg, scale, scale);
		ofxCv::copyGray(smallImg, smallGray);
	}

	void threadedFunction() {

	}

	cv::Mat largeImg;
	cv::Mat smallImg;
	cv::Mat smallGray;

	ofVideoGrabber* grabber;

	float scale = 0.1;
	float width;
	float height;


private:


};