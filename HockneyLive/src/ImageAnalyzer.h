#pragma once

#include "ofMain.h"
#include "ofxCv.h"

struct flowRectangle {
	ofRectangle rect;
	float flowMag;
	ofVec2f flow;
	ofRectangle outputRect;
	void calculateFlow(ofxCv::FlowFarneback* _flow) {
		flow = _flow->getAverageFlowInRegion(rect);
		flowMag = sqrt(flow.x * flow.x + flow.y * flow.y);
	}
	int id;
};

class ImageAnalyzer: public ofThread {
public:
	ImageAnalyzer();

	void setup(ofVideoGrabber* _grabber) {
		width = _grabber->getWidth();
		height = _grabber->getHeight();
		grabber = _grabber;
	}

	void copyImage() {

	}

	void threadedFunction() {
		//while (1) {
			cout << "Thread Started!" << endl;
			ofxCv::copy(*grabber, largeImg);
			ofxCv::resize(largeImg, smallImg, scale, scale);
			ofxCv::copyGray(smallImg, smallGray);
			flow.calcOpticalFlow(smallGray);
			cout << "Thread Done!" << endl;
		//}
	}

	cv::Mat largeImg;
	cv::Mat smallImg;
	cv::Mat smallGray;

	ofxCv::FlowFarneback flow;

	ofVideoGrabber* grabber;

	float scale = 0.1;
	float width;
	float height;


private:


};