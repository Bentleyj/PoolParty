#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "particle.h"
#include "line.hpp"

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
		ofParameter<int> noiseIterations;
		ofParameter<float> noiseSize;
        ofParameter<float> noiseSpeed;
		ofParameter<float> noiseScale;
        ofParameter<float> horizon;

		vector<Particle> particles;
        vector<line> linesBottom;
        vector<line> linesTop;

		vector<ofVec2f> points;
};
