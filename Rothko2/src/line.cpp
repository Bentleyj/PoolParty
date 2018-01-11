//
//  line.cpp
//  Rothko2
//
//  Created by cafe on 11/01/2018.
//

#include "line.hpp"

#define LINE_RESOLUTION 300

line::line() {
    offset = ofRandom(10000);
}

void line::setup() {
    for(int i = 0; i < LINE_RESOLUTION; i++) {
        ofVec2f p;
        p.x = i * ofGetWidth() / LINE_RESOLUTION;
        p.y = ofGetHeight() / 2;
        points.push_back(p);
    }
}

void line::update(line* comparatorLine) {
    if(comparatorLine == nullptr) {
        return;
    } else {
        for(int i = 0; i < noiseIterations; i++) {
            float o = i;
            for(int j = 0; j < points.size(); j++) {
                points[j].y = comparatorLine->points[j].y + sign * ofNoise(ofGetElapsedTimef() * noiseSpeed, points[j].x * (noiseScale*o), offset) * noiseSize*o;
                points[j].y += sign * baseHeight;
            }
            
        }
    }
}

void line::draw() {
    ofPushStyle();
    ofSetColor(col);
    for(int i = 0; i < points.size()-1; i++) {
        ofDrawLine(points[i], points[i+1]);
    }
    ofPopStyle();
}
