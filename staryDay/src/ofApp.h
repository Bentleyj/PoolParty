#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "spectrumFinder.hpp"
#include "ofxProcessFFT.h"

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
            
        vector<ofColor> cols;
    
        ofVec3f camPosTarget;
        ofVec3f camLookAtTarget;
    
        ofVbo vbo;
        ofTexture starSprite;
    
        float rotation;
    
        ofShader starPoints, fade;
    
        vector<ofVec3f> sizes;
        vector<ofVec3f> points;
        vector<ofFloatColor> colors;
    
        float radius;
    
        ofEasyCam cam;
    
        ProcessFFT fft;
    
        bool showGui;
};
