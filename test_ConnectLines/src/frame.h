#pragma once

#include "ofMain.h"

class frame : public ofRectangle {
public:
	ofVec2f startPoint;
	ofVec2f endPoint;
	vector<ofPolyline>* lines;
	ofImage *img;
	float angleBetweenTwoPoints(ofVec2f p1, ofVec2f p2);
	void draw(float offset);
	bool isInsideBox(ofVec2f p);
	ofVec2f getNearestEdge(ofVec2f p1, ofVec2f p2);
	float distance(ofVec2f p1, ofVec2f p2);
};