#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#define NUM_CELLS_X 5
#define NUM_CELLS_Y 5

struct flowRectangle {
	ofRectangle rect;
	float flowMag;
	ofVec2f flow;
	int id;
	void calculateFlow(ofxCv::FlowFarneback* _flow) {
		flow = _flow->getAverageFlowInRegion(rect);
		flowMag = sqrt(flow.x * flow.x + flow.y * flow.y);
	}
};

class ImageAnalyzer: public ofThread {
public:
	ImageAnalyzer();

	// Setup
	void setup(ofVideoGrabber* _grabber) {
		width = _grabber->getWidth();
		height = _grabber->getHeight();
		grabber = _grabber;
		setupGrid();
	}

	void setupGrid() {
		if (grabber != nullptr) {
			int id = 0;
			float OffsetAmount = 50;
			float xOffset = 0;
			float yOffset = 0;
			float widthOffset = 0;
			float heightOffset = 0;
			int smallCellWidth = width * scale / NUM_CELLS_X;
			int smallCellHeight = height * scale / NUM_CELLS_Y;
			for (int x = 0; x < NUM_CELLS_X; x++) {
				for (int y = 0; y < NUM_CELLS_Y; y++) {

					flowRectangle small;
					small.rect = ofRectangle(x + 1, y + 1, smallCellWidth - 2, smallCellHeight - 2);
					small.flowMag = 0;
					small.flow = ofVec2f(0, 0);
					small.id = id;
					orderedIDs.push_back(id);
					id++;

					flowGrid.push_back(small);

					ofRectangle large = ofRectangle(x * scale, y * scale, smallCellWidth * scale, smallCellHeight * scale);
					outputRectangles.push_back(large);
				}
			}
		}
		else {
			cout << "ImageAnalyzer::setupGrid() video grabber not defined" << endl;
		}
	}

	vector<ofRectangle> getOutputRectangles() {
		return outputRectangles;
	}

	// Function
	void copyImage() {
		ofxCv::copy(*grabber, largeImg);
		ofxCv::resize(largeImg, smallImg, scale, scale);
		ofxCv::copyGray(smallImg, smallGray);
	}

	static bool compareFlow(flowRectangle a, flowRectangle b) {
		return (a.flowMag > b.flowMag);
	}

	void threadedFunction() {
		analyzeImage();	
		for (int i = 0; i < flowGrid.size(); i++) {
			lock();
			orderedIDs[i] = flowGrid[i].id;
			unlock();
		}
		cout << "Thread done!" << endl;
	}

	void unthreadedAnalyze() {
		analyzeImage();
		for (int i = 0; i < flowGrid.size(); i++) {
			orderedIDs[i] = flowGrid[i].id;
		}
	}

	void analyzeImage() {
		copyImage();
		flow.calcOpticalFlow(smallGray);
		for (int i = 0; i < flowGrid.size(); i++) {
			flowGrid[i].calculateFlow(&flow);
		}
		std::sort(flowGrid.begin(), flowGrid.end(), compareFlow);
	}

	cv::Mat largeImg;
	cv::Mat smallImg;
	cv::Mat smallGray;

	ofxCv::FlowFarneback flow;

	ofVideoGrabber* grabber;

	vector<flowRectangle> flowGrid;
	vector<ofRectangle> outputRectangles;
	vector<int> orderedIDs;

	float scale = 0.1;
	float width;
	float height;

private:


};