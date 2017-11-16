#include "Cell.h"

Cell::Cell() {
    debugColor = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Cell::resizeInputRect() {
	float randomRange = 100;
	float randomSizeRange = 50;
	ofVec3f randomOffset;
	randomOffset.x = ofRandom(-randomRange, randomRange);
	randomOffset.y = ofRandom(-randomRange, randomRange);
	randomOffset.z = ofRandom(0, randomSizeRange);
    
    offsetInputRect = inputRect;
    
	offsetInputRect.x = inputRect.x + randomOffset.x;
	offsetInputRect.y = inputRect.y + randomOffset.y;
	offsetInputRect.width = inputRect.width + randomOffset.z;
	offsetInputRect.height = inputRect.height + randomOffset.z;
    
    offsetInputRect.x += flow.x * scale;
    offsetInputRect.y += flow.y * scale;

	if (offsetInputRect.x < 0) {
		float offLeft = abs(offsetInputRect.x);
		offsetInputRect.x = 0;
	}
	if (offsetInputRect.y < 0) {
		float offTop = abs(offsetInputRect.y);
		offsetInputRect.y = 0;
	}
	if (offsetInputRect.x + offsetInputRect.width > img->getWidth()) {
		float offRight = offsetInputRect.x + offsetInputRect.width - img->getWidth();
		offsetInputRect.x -= offRight;
	}
	if (offsetInputRect.y + offsetInputRect.height > img->getHeight()) {
		float offBottom = offsetInputRect.y + offsetInputRect.height - img->getHeight();
		offsetInputRect.y -= offBottom;
	}
}

void Cell::update(ofRectangle _rect, ofVec2f _flow) {
	if (ofGetElapsedTimef() - lastSwapTime > swapDuration) {
		flow = _flow;
		inputRect = _rect;
		resizeInputRect();
		lastSwapTime = ofGetElapsedTimef();
		flow.x = ofLerp(flow.x, 0, 0.01);
		flow.y = ofLerp(flow.y, 0, 0.01);
	}
}

void Cell::draw(int x, int y, int width, int height) {
    ofPushStyle();
	ofPushMatrix();
	ofScale(-1, 1);
	ofTranslate(-1650, 0);
    ofSetColor(255);
	img->drawSubsection(x, y, width, height, offsetInputRect.x, offsetInputRect.y, offsetInputRect.width, offsetInputRect.height);
	ofPopMatrix();
    ofPopStyle();
}

void Cell::drawDebug() {
    ofPushStyle();
	ofNoFill();
    ofSetColor(debugColor);
    ofSetLineWidth(5);
    ofDrawRectangle(offsetInputRect.x, offsetInputRect.y, offsetInputRect.width, offsetInputRect.height);
    ofPopStyle();
}

void Cell::draw(ofRectangle _rect) {
	draw(_rect.x, _rect.y, _rect.width, _rect.height);
}
