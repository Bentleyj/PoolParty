#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#define NUM_CELLS_X 10
#define NUM_CELLS_Y 10

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
            ofRectangle large = ofRectangle(0, 0, width, height);
            outputRectangles = fillRectWithSquares(large);
            vector<ofRectangle> smallRectangles = fillRectWithSquares(ofRectangle(large.x * scale, large.y * scale, large.width * scale, large.height * scale));
            for(int i = 0; i < smallRectangles.size(); i++) {
                flowRectangle small;
                small.rect = smallRectangles[i];//ofRectangle(x * smallCellWidth + 1, y * smallCellHeight + 1, smallCellWidth - 2, smallCellHeight - 2);
                small.flowMag = 0;
                small.flow = ofVec2f(0, 0);
                small.id = i;
                orderedIDs.push_back(i);
                orderedFlows.push_back(ofVec2f(0, 0));
                flowGrid.push_back(small);
            }
		}
		else {
			cout << "ImageAnalyzer::setupGrid() video grabber not defined" << endl;
		}
	}
    
    vector<ofRectangle> fillRectWithSquares(ofRectangle _outerRect) {
        vector<ofRectangle> squares;
        float width = _outerRect.width;
        float height = _outerRect.height;
        float cellWidth = width / NUM_CELLS_X;
        float cellHeight = cellWidth;
        float xStep = cellWidth;
        float yStep = cellHeight - ((cellHeight * NUM_CELLS_Y) - height) / NUM_CELLS_Y;
        for(int x = 0; x < NUM_CELLS_X; x++) {
            for(int y = 0; y < NUM_CELLS_Y - 1; y++) {
                ofRectangle rect = ofRectangle(x * xStep, y * yStep, cellWidth, cellHeight);
                squares.push_back(rect);
            }
        }
        return squares;
    }

	vector<ofRectangle> getOutputRectangles() {
		return outputRectangles;
	}
    
    void drawDebug() {
        ofPushMatrix();
        ofNoFill();
        ofTranslate(0, 0);
        ofxCv::drawMat(largeImg, 0, 0);
        ofSetColor(255);
        for(int i = 0; i < outputRectangles.size(); i++) {
            ofDrawRectangle(outputRectangles[i]);
        }
        ofTranslate(0, largeImg.rows);
        ofxCv::drawMat(smallImg, 0, 0);
        for(int i = 0; i < flowGrid.size(); i++) {
            ofDrawRectangle(flowGrid[i].rect);
        }
        ofTranslate(smallImg.cols, 0);
        ofxCv::drawMat(smallGray, 0, 0);
        for(int i = 0; i < flowGrid.size(); i++) {
            ofDrawRectangle(flowGrid[i].rect);
        }
        ofPopMatrix();
    }

	// Function
	void copyImage() {
        lock();
		ofxCv::copy(*grabber, largeImg);
        unlock();
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
            orderedFlows[i] = flowGrid[i].flow;
			unlock();
		}
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
	cv::Mat flipLarge;

	ofxCv::FlowFarneback flow;

	ofVideoGrabber* grabber;

	vector<flowRectangle> flowGrid;
	vector<ofRectangle> outputRectangles;
	vector<int> orderedIDs;
    
    vector<ofVec2f> orderedFlows;

	float scale = 0.1;
	float width;
	float height;

private:


};
