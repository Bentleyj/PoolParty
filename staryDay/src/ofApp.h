#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "spectrumFinder.hpp"

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
        
        ofVec3f cartesianToSpherical(ofVec3f point);
        ofVec3f sphericalToCartesian(ofVec3f point);
        ofVec3f starCoordsToSpherical(double ra, double de);
    
        ofxPanel gui;
        ofParameterGroup starGroup;
        ofParameter<float> starDensity;
        ofParameter<float> maxStarSize;
        ofParameter<float> rotSpeed;
        ofParameter<float> trailLength;
        ofParameter<float> threshold;

        ofParameterGroup cameraGroup;
        ofParameter<bool> freeCamera;
        ofParameter<float> ra;
        ofParameter<float> de;
    
        ofParameter<int> bufferSize;
    
        ofFbo drawBuffer, fadeBufferDraw, fadeBufferSave;
    
        ofImage img;
    
        spectrumFinder colorFinder;
    
        vector<ofColor> cols;
    
        ofVec3f camPosTarget;
        ofVec3f camLookAtTarget;
    
        ofVboMesh celestialSphere;
    
        float rotation;
    
        ofShader starPoints, fade;
    
        vector<float> pointSize;
    
        float radius;
    
        ofEasyCam cam;
		
};
