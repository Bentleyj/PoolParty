#pragma once

#include "ofMain.h"
#include "frame.h"

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

		vector<ofPolyline> lines1;
		vector<ofPolyline> lines2;
		vector<frame> frames;

		ofImage img1;
		ofImage img2;

		enum { display, draw1, draw2 } state;

		ofVec2f linkPoint;
		
};
