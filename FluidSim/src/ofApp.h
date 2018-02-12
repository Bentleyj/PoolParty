#pragma once

#include "ofMain.h"
#include "Cell.hpp"
#include "ofMatrix2x2.h"

#define X_RES 10
#define Y_RES 10

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
    
        float hash(float seed) {
            float integral;
            return modf(sin(seed)*158.5453, &integral);
        }
        ofVec4f getRand4(float seed) {
            return ofVec4f(hash(seed),hash(seed+123.21),hash(seed+234.32),hash(seed+453.54));
        }
        ofVec4f randS()
        {
            ofVec4f v;
            v.x = ofRandom(-0.5, 0.5);
            v.y = ofRandom(-0.5, 0.5);
            v.z = ofRandom(-0.5, 0.5);
            v.w = ofRandom(-0.5, 0.5);
        }
        float getRot(ofVec2f uv, float sc);

    
    Cell cellsFlip[X_RES][Y_RES];
    Cell cellsFlop[X_RES][Y_RES];

    
    const float ang = 2.0*3.1415926535/float(RotNum);
    ofMatrix2x2 m = ofMatrix2x2(cos(ang),sin(ang),-sin(ang),cos(ang));
};
