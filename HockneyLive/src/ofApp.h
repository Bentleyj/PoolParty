#pragma once

#define IMG_SCALE 10

#include "ofMain.h"
#include "ofxNestedFileLoader.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "Cell.h"

struct flowRectangle {
	ofRectangle rect;
	float flowMag;
	ofVec2f flow;
	void calculateFlow(ofxCv::FlowFarneback* _flow) {
		flow = _flow->getAverageFlowInRegion(rect);
		flowMag = sqrt(flow.x * flow.x + flow.y * flow.y);
	}
};

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

		bool compareFlow(flowRectangle a, flowRectangle b) {
			return (a.flowMag < b.flowMag);
		}

		vector<string> videoPaths;
		ofVideoGrabber cameraStream;
		ofVideoPlayer player;

		ofxCv::FlowFarneback flow;

		vector<int> topRectangles;

		int topFlowIndex;

		vector<flowRectangle> smallGrid;
		vector<ofRectangle> largeGrid;
		vector<ofRectangle> displayPositions;

		vector<Cell> cells;

		float timeBetweenChecks;
		float lastCheckTime;

		ofImage largeImg;
		ofImage smallImg;
		ofImage smallGray;
};
