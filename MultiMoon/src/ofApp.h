#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Moon.h"

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
    
        ofxPanel gui;
        ofParameter<float> x, y, width, horizon;
        ofParameter<bool> animate;
        ofParameter<int> bufferSize;
        ofFbo top, bottom, viewBuffer;
    
        int index;
        
        vector<Moon> moons;
    
};
