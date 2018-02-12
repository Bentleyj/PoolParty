#pragma once

#include "ofMain.h"
#include "Cell.hpp"
#include "ofMatrix2x2.h"

#define X_RES 1000
#define Y_RES 1000

#define RotNum 5
#define angRnd 0.0
#define posRnd 0.0

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
    
        ofShader fluidSolver;
        ofShader fluidShower;
    
        ofFbo solverBuffer;
        ofFbo copyBuffer;
        ofFbo randomBuffer;
};
