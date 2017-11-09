#pragma once

#define IMG_SCALE 10

#include "ofMain.h"
#include "ofxNestedFileLoader.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "Cell.h"
#include "ImageAnalyzer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofShader crossProcess;
    
        ofImage curveTexture;
    
        ofxPanel gui;
        ofParameter<float> flowScale;

		vector<string> videoPaths;
		ofVideoGrabber cameraStream;
		ofVideoPlayer player;

		ofxCv::FlowFarneback flow;

		vector<int> topRectangles;

		ofImage largeImg;

		int topFlowIndex;

		vector<int> sortedFlowRectangles;
		vector<ofRectangle> outputRectangles;
		vector<ofRectangle> displayPositions;

		vector<Cell> cells;

		ofMutex mutex;

		float timeBetweenChecks;
		float lastCheckTime;

		ImageAnalyzer analyzer;
};
