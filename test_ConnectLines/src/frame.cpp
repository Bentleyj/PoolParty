#include "Frame.h"

Frame::Frame() {
    img = nullptr;
}

float Frame::angleBetweenTwoPoints(ofVec2f p1, ofVec2f p2)
{
	return atan2(p2.y - p1.y, p2.x - p1.x);
}

void Frame::draw() 
{
    float offset = 0.0;
    
	ofPushMatrix();
	ofPushStyle();
	ofSetColor(255);
    if(img != nullptr)
        img->drawSubsection(x, y, width, height, x, y - offset);
	ofPopStyle();
	ofPushStyle();
	ofTranslate(0, offset);
	ofNoFill();
    
    vector<ofPoint> verts = line->getVertices();
    if (verts.size() > 2) {
        for (int i = 1; i < verts.size() - 1; i++) {
            if (isInsideBox(verts[i])) {
                ofDrawLine(verts[i], verts[i + 1]);
            }
            if (!isInsideBox(verts[i - 1]) && isInsideBox(verts[i])) {
                startPoint = getNearestEdge(verts[i], verts[i - 1]);
                ofSetColor(0, 0, 255);
                ofDrawLine(verts[i], verts[i - 1]);
            }
            else if (isInsideBox(verts[i]) && !isInsideBox(verts[i + 1])) {
                endPoint = getNearestEdge(verts[i], verts[i + 1]);
                ofSetColor(0, 0, 255);
                ofDrawLine(verts[i], verts[i + 1]);
            }
        }
    }
    
	ofSetColor(0, 255, 0);
	ofDrawCircle(startPoint, 5);
	ofSetColor(255, 0, 0);
	ofDrawCircle(endPoint, 5);

	ofPopMatrix();

	ofSetColor(255);
	ofDrawRectangle(x, y, width, height);
	ofPopStyle();
}

bool Frame::isInsideBox(ofVec2f p)
{
	if (p.x > x && p.x < x + width) {
		if (p.y > y && p.y < y + height) {
			return true;
		}
	}
	return false;
}

ofVec2f Frame::getNearestEdge(ofVec2f p1, ofVec2f p2)
{
	float m = (p2.y - p1.y) / (p2.x - p1.x);
	float b = p2.y - m * p2.x;

	float leftX = x;
	float leftY = m * leftX + b;

	float rightX = x + width;
	float rightY = m * rightX + b;

	float topY = y;
	float topX = (topY - b) / m;

	float bottomY = y + height;
	float bottomX = (bottomY - b) / m;

	float leftDist = distance(p1, ofVec2f(leftX, leftY));
	float rightDist = distance(p1, ofVec2f(rightX, rightY));
	float topDist = distance(p1, ofVec2f(topX, topY));
	float bottomDist = distance(p1, ofVec2f(bottomX, bottomY));

	ofVec3f nearest;
	nearest = ofVec2f(leftX, leftY);

	float minDist = width + height;
	if (leftDist < minDist) {
		minDist = leftDist;
	}
	if (rightDist < minDist) {
		minDist = rightDist;
		nearest = ofVec2f(rightX, rightY);
	}
	if (topDist < minDist) {
		minDist = topDist;
		nearest = ofVec2f(topX, topY);
	}
	if (bottomDist < minDist) {
		nearest = ofVec2f(bottomX, bottomY);
	}
	return nearest;
}

float Frame::distance(ofVec2f p1, ofVec2f p2)
{
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

Frame::~Frame() {
    img = nullptr;
    line = nullptr;
}
