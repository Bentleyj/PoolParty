#pragma once

#include "ofMain.h"

class Frame : public ofRectangle {
public:
    //Fields
	ofVec2f startPoint;
    
	ofVec2f endPoint;
    
    ofVec2f targetStartPoint;
    
    ofVec2f targetEndPoint;
    
	ofPolyline* line;
    
	ofImage *img;

	ofShader shader;
    
    float r;
    
    //Functionality
    Frame();
    ~Frame();
    
    void draw();

	float angleBetweenTwoPoints(ofVec2f p1, ofVec2f p2);
    ofVec2f getMidpoint(ofVec2f p1, ofVec2f p2);
    float distance(ofVec2f p1, ofVec2f p2);
    
	bool isInsideBox(ofVec2f p);
    
	ofVec2f getNearestEdge(ofVec2f p1, ofVec2f p2);
    
    
    void setTargetStartPoint(ofVec2f p);
    void setTargetEndPoint(ofVec2f p);
    ofVec2f getTargetPoint(ofVec2f p);
    
};
