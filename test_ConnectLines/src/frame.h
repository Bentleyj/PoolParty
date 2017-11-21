#pragma once

#include "ofMain.h"

class frame : public ofRectangle {
public:
	ofVec2f startPoint;
	ofVec2f endPoint;
	vector<ofPolyline>* lines;
	float angleBetweenTwoPoints(ofVec2f p1, ofVec2f p2);
	void draw();
	bool isInsideBox(ofVec2f p);
	ofVec2f getNearestEdge(ofVec2f p1, ofVec2f p2);
	float distance(ofVec2f p1, ofVec2f p2);
};