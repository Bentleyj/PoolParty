//
//  line.cpp
//  Rothko2
//
//  Created by cafe on 11/01/2018.
//

#include "line.hpp"

#define LINE_RESOLUTION 100

line::line() {
    
}

void line::setup() {
    for(int i = 0; i < LINE_RESOLUTION; i++) {
        ofVec2f p;
        p.x = i * ofGetWidth() / LINE_RESOLUTION;
        p.y = ofGetHeight() / 2;
        points.push_back(p);
    }
}

void line::update() {
    for(int i = 0; i < noiseIterations; i++) {
        float offset = i;
        for(int i = 0; i < points.size(); i++) {
            points[i].y = ofGetWidth()/2 + (0.5 - ofNoise(ofGetElapsedTimef() * noiseSpeed, points[i].x * (noiseScale*offset), offset)) * noiseSize*offset;
            
        }
    }
}

void line::draw() {
    ofPushStyle();
    ofSetColor(255);
    for(int i = 0; i < points.size()-1; i++) {
        ofDrawLine(points[i], points[i+1]);
    }
    ofPopStyle();
}
