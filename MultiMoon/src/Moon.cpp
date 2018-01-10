//
//  Moon.cpp
//  MultiMoon
//
//  Created by cafe on 09/01/2018.
//

#include "Moon.h"

Moon::Moon() {
    offset = ofRandom(0, 10000);
};

void Moon::update() {
    x = ofNoise(ofGetElapsedTimef() * 0.01 + offset) * ofGetWidth() * 2.0;
    y = ofLerp(y, targetY, speed);
}

void Moon::draw() {
    
}

void Moon::drawTop() {
    ofPushStyle();
    ofSetColor(color);
    ofDrawCircle(x, y, radius);
    ofSetColor(0);
    ofDrawRectangle(0, *horizon, ofGetWidth(), ofGetHeight());
    ofPopStyle();
}

void Moon::drawBottom() {
    ofPushStyle();
    ofSetColor(color.r, color.g, color.b, ofMap(y, *horizon-radius, *horizon+radius, 200, 0, true));
    ofDrawTriangle(x, *horizon, x + width/2, ofGetHeight(), x - width/2, ofGetHeight());
    ofPopStyle();
}

float Moon::max(float a, float b) {
    if(a > b) return a;
    return b;
}
