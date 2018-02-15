#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "star.hpp"
#include "ofxCsv.h"

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
    
        void pChanged(float & p);
    
        ofVec3f cartesianToSpherical(ofVec3f point);
        ofVec3f sphericalToCartesian(ofVec3f point);
        ofVec3f starCoordsToSpherical(double ra, double de);
    
        ofxPanel gui;
        ofParameterGroup starGroup;
        ofParameter<float> starDensity;
        ofParameter<float> maxStarSize;


        ofParameterGroup cameraGroup;
        ofParameter<bool> freeCamera;
        ofParameter<float> ra;
        ofParameter<float> de;
    
    
    
        ofVec3f camPosTarget;
        ofVec3f camLookAtTarget;
    
        ofVboMesh celestialSphere;
    
        ofxCsv starData;
    
        ofShader starPoints;
    
        vector<float> pointSize;
    
        ofxXmlSettings starsData;
    
        vector<star> stars;
    
        float radius;
    
        ofMesh sphere;
    
        ofEasyCam cam;
		
};
